package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/go-chi/chi/v5"
)

type Task struct {
	ID     int    `json:"id"`
	Name   string `json:"name"`
	Status string `json:"status"` // "pending", "processing", "completed"
}

var (
	mu       sync.Mutex
	tasks    []Task
	nextID   = 1
	taskChan = make(chan Task, 100) // Buffered channel for tasks, use environment variable for size in real apps
)

func main() {
	fmt.Println("Welcome")

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	// Start worker pool
	numWorkers := 3 // Use environment variable for number of workers in real apps
	var wg sync.WaitGroup
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go worker(ctx, i+1, &wg)
	}

	server := &http.Server{
		Addr:    ":8080",
		Handler: setupRoutes(),
	}

	// Start server
	go func() {
		fmt.Println("Serving on :8080...")
		if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("listen: %v", err)
		}
	}()

	// Wait for interrupt
	quit := make(chan os.Signal, 1)
	signal.Notify(quit, syscall.SIGINT, syscall.SIGTERM)
	<-quit

	fmt.Println("\nShutting down gracefully...")

	shutdownCtx, shutdownCancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer shutdownCancel()

	if err := server.Shutdown(shutdownCtx); err != nil {
		log.Printf("server shutdown error: %v", err)
	}

	cancel()
	close(taskChan)
	wg.Wait()

	shutdown()
}

func worker(ctx context.Context, id int, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Printf("Worker %d started\n", id)

	for {
		select {
		case <-ctx.Done():
			fmt.Printf("Worker %d stopped\n", id)
			return
		case task, ok := <-taskChan:
			if !ok {
				fmt.Printf("Worker %d stopped\n", id)
				return
			}

			fmt.Printf("Worker %d processing task %d: %s\n", id, task.ID, task.Name)

			// Update task status to processing
			mu.Lock()
			for i := range tasks {
				if tasks[i].ID == task.ID {
					tasks[i].Status = "processing"
					break
				}
			}
			mu.Unlock()

			// Simulate work
			time.Sleep(2 * time.Second)

			// Update task status to completed
			mu.Lock()
			for i := range tasks {
				if tasks[i].ID == task.ID {
					tasks[i].Status = "completed"
					break
				}
			}
			mu.Unlock()

			fmt.Printf("Worker %d completed task %d\n", id, task.ID)
		}
	}
}

func setupRoutes() *chi.Mux {
	r := chi.NewRouter()

	r.Route("/api", func(r chi.Router) {
		// Public routes (no permission required)
		r.Get("/status", func(w http.ResponseWriter, r *http.Request) {
			w.Header().Set("Content-Type", "application/json")
			if _, err := w.Write([]byte(`{"status":"ok"}`)); err != nil {
				log.Printf("write /api/status: %v", err)
			}
		})

		// Read-only routes (require "read" permission)
		r.Group(func(r chi.Router) {
			r.Use(RequirePermission("read"))

			r.Get("/tasks", func(w http.ResponseWriter, r *http.Request) {
				mu.Lock()
				defer mu.Unlock()
				w.Header().Set("Content-Type", "application/json")
				if err := json.NewEncoder(w).Encode(tasks); err != nil {
					log.Printf("encode tasks: %v", err)
				}
			})

			r.Get("/tasks/{id}", func(w http.ResponseWriter, r *http.Request) {
				idStr := chi.URLParam(r, "id")
				var id int
				if _, err := fmt.Sscanf(idStr, "%d", &id); err != nil {
					http.Error(w, "invalid task id", http.StatusBadRequest)
					return
				}

				mu.Lock()
				defer mu.Unlock()
				for _, task := range tasks {
					if task.ID == id {
						w.Header().Set("Content-Type", "application/json")
						if err := json.NewEncoder(w).Encode(task); err != nil {
							log.Printf("encode task: %v", err)
						}
						return
					}
				}
				http.Error(w, "task not found", http.StatusNotFound)
			})
		})

		// Write routes (require "write" permission)
		r.Group(func(r chi.Router) {
			r.Use(RequirePermission("write"))

			r.Post("/tasks", func(w http.ResponseWriter, r *http.Request) {
				var input struct {
					Name string `json:"name"`
				}
				if err := json.NewDecoder(r.Body).Decode(&input); err != nil || input.Name == "" {
					http.Error(w, "invalid body", http.StatusBadRequest)
					return
				}

				mu.Lock()
				task := Task{ID: nextID, Name: input.Name, Status: "pending"}
				nextID++
				tasks = append(tasks, task)
				mu.Unlock()

				select {
				case taskChan <- task:
				default:
					log.Printf("task queue full, task %d not queued", task.ID)
				}

				w.Header().Set("Content-Type", "application/json")
				w.WriteHeader(http.StatusCreated)
				if err := json.NewEncoder(w).Encode(task); err != nil {
					log.Printf("encode task: %v", err)
				}
			})

			r.Put("/tasks/{id}", func(w http.ResponseWriter, r *http.Request) {
				idStr := chi.URLParam(r, "id")
				var id int
				if _, err := fmt.Sscanf(idStr, "%d", &id); err != nil {
					http.Error(w, "invalid task id", http.StatusBadRequest)
					return
				}

				var input struct {
					Status string `json:"status"`
				}
				if err := json.NewDecoder(r.Body).Decode(&input); err != nil {
					http.Error(w, "invalid body", http.StatusBadRequest)
					return
				}

				mu.Lock()
				defer mu.Unlock()
				for i := range tasks {
					if tasks[i].ID == id {
						tasks[i].Status = input.Status
						w.Header().Set("Content-Type", "application/json")
						if err := json.NewEncoder(w).Encode(tasks[i]); err != nil {
							log.Printf("encode task: %v", err)
						}
						return
					}
				}
				http.Error(w, "task not found", http.StatusNotFound)
			})
		})

		// Admin-only routes (require "admin" permission)
		r.Group(func(r chi.Router) {
			r.Use(RequirePermission("admin"))

			r.Delete("/tasks/{id}", func(w http.ResponseWriter, r *http.Request) {
				idStr := chi.URLParam(r, "id")
				var id int
				if _, err := fmt.Sscanf(idStr, "%d", &id); err != nil {
					http.Error(w, "invalid task id", http.StatusBadRequest)
					return
				}

				mu.Lock()
				defer mu.Unlock()
				for i := range tasks {
					if tasks[i].ID == id {
						tasks = append(tasks[:i], tasks[i+1:]...)
						w.WriteHeader(http.StatusNoContent)
						return
					}
				}
				http.Error(w, "task not found", http.StatusNotFound)
			})
		})

		r.MethodNotAllowed(func(w http.ResponseWriter, r *http.Request) {
			http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		})
	})

	return r
}

func RequirePermission(permission string) func(http.Handler) http.Handler {
	return func(next http.Handler) http.Handler {
		return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
			// In real apps, check user permissions here
			if permission == "read" || permission == "write" { // Simulate permission check, omit admin for now
				next.ServeHTTP(w, r) // good to go!
				return
			}
			http.Error(w, "Unauthorized", http.StatusUnauthorized)
		})
	}
}

func shutdown() {
	fmt.Println("Shutdown complete")
}
