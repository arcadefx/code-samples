# Task Worker API

A RESTful API service with an asynchronous task processing system using a worker pool pattern.

## What It Does

Provides a complete HTTP API for managing tasks that are processed asynchronously by a pool of background workers:
- Accepts task submissions via REST endpoints
- Queues tasks in a buffered channel
- Processes tasks concurrently using a worker pool
- Tracks task status (pending, processing, completed)
- Implements graceful shutdown handling
- Role-based access control for API endpoints

## Key Features

### Worker Pool Pattern
- Configurable number of concurrent workers (default: 3)
- Buffered task channel (capacity: 100)
- Automatic task status tracking
- Simulated 2-second processing time per task

### REST API Endpoints

#### Public
- `GET /api/status` - Health check

#### Read Permission Required
- `GET /api/tasks` - List all tasks
- `GET /api/tasks/{id}` - Get specific task

#### Write Permission Required
- `POST /api/tasks` - Create new task

## Technology Stack

- **Router**: [chi/v5](https://github.com/go-chi/chi) - Lightweight HTTP router
- **Concurrency**: Goroutines, channels, WaitGroups
- **Graceful Shutdown**: Context cancellation and server shutdown

## Architecture

```
HTTP Request → Router → Permission Middleware → Handler
                                ↓
                          Task Channel
                                ↓
                          Worker Pool (3 workers)
                                ↓
                   Task Processing (status updates)
```

## Running the Service

```bash
go run main.go
```

Server starts on `http://localhost:8080`

## API Examples

### Create a task
```bash
curl -X POST http://localhost:8080/api/tasks \
  -H "Content-Type: application/json" \
  -d '{"name":"Process data"}'
```

### List all tasks
```bash
curl http://localhost:8080/api/tasks
```

### Get task status
```bash
curl http://localhost:8080/api/tasks/1
```

## Graceful Shutdown

Press `Ctrl+C` to trigger graceful shutdown:
1. Stops accepting new HTTP requests
2. Cancels worker context
3. Closes task channel
4. Waits for workers to finish current tasks
5. 5-second timeout for shutdown completion

## Environment Considerations

For production use, consider making these configurable via environment variables:
- Number of workers
- Task channel buffer size
- Server port
- Shutdown timeout
