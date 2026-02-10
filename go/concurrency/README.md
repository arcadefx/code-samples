# Concurrency with Semaphore

This project demonstrates controlled concurrency using a semaphore pattern to limit the number of concurrent workers.

## What It Does

Simulates making multiple API calls with a limited worker pool:
- Limits concurrent operations using a semaphore (buffered channel)
- Processes 10 API calls with a maximum of 2 concurrent workers
- Collects results through a dedicated results channel
- Demonstrates proper coordination with WaitGroups

## Key Concepts Demonstrated

- **Semaphore pattern** using buffered channels to limit concurrency
- **Worker pool** with a maximum number of concurrent goroutines
- **Channel coordination** for collecting results
- **Proper goroutine synchronization** with `sync.WaitGroup`

## How It Works

1. Creates a semaphore channel with capacity 2 (maxWorkers)
2. Launches 10 goroutines that acquire/release semaphore slots
3. Each worker simulates API work with varying sleep times
4. Results are collected and summed before being sent

## Running the Sample

```bash
go run main.go
```

## Output

Shows the progression of API calls being started and completed, respecting the maximum worker limit of 2 concurrent operations.
