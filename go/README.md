# Go Code Samples

A collection of Go programming examples demonstrating various patterns, concurrency concepts, and best practices.

## Projects Overview

### [channels](channels/)
Demonstrates concurrent URL checking using Go channels, goroutines, and WaitGroups. Shows proper channel management and goroutine synchronization.

**Key Topics**: Channels, Goroutines, WaitGroups, HTTP requests

### [command-dispatcher](command-dispatcher/)
Implements a command dispatcher pattern with role-based access control (RBAC). Maps string commands to functions dynamically.

**Key Topics**: Function maps, RBAC, Dynamic dispatch, Error handling

### [concurrency](concurrency/)
Shows controlled concurrency using the semaphore pattern to limit the number of concurrent workers processing tasks.

**Key Topics**: Semaphores, Worker pools, Controlled concurrency, Result collection

### [oop-like](oop-like/)
Demonstrates object-oriented programming patterns in Go using interfaces, structs, and methods. Implements a simple grocery bag system.

**Key Topics**: Interfaces, Structs, Methods, Constructor patterns

### [practice-go](practice-go/)
A collection of fundamental Go programming examples covering common operations and patterns for learning.

**Key Topics**: Slices, Sorting, Ranges, String manipulation, Package organization

### [task-worker-api](task-worker-api/)
A production-ready RESTful API with asynchronous task processing using a worker pool. Features graceful shutdown and role-based permissions.

**Key Topics**: REST API, Worker pools, Graceful shutdown, Chi router, Channels, Task queues

## Running the Examples

Each project can be run independently. Navigate to any project directory and run:

```bash
go run main.go
```

Or for the channels example:
```bash
go run sample.go
```

## Requirements

- Go 1.25.1 or higher
- Dependencies are managed with Go modules (`go.mod`)

## Learning Path

Recommended order for beginners:

1. **practice-go** - Start with fundamentals
2. **oop-like** - Learn Go's approach to OOP
3. **channels** - Introduction to concurrency
4. **concurrency** - Advanced concurrency patterns
5. **command-dispatcher** - Design patterns
6. **task-worker-api** - Real-world application

## Additional Notes

All projects use Go modules for dependency management. Run `go mod tidy` in any project directory to ensure dependencies are properly installed.
