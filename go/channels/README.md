# Channels Sample

This project demonstrates concurrent URL checking using Go channels, goroutines, and WaitGroups.

## What It Does

Concurrently checks the availability of multiple GitHub profile URLs using:
- **Channels** for communication between goroutines
- **WaitGroups** to coordinate goroutine completion
- **HTTP GET requests** to verify URL accessibility

## Key Concepts Demonstrated

- Creating and using buffered channels
- Launching concurrent goroutines
- Synchronizing with `sync.WaitGroup`
- Properly closing channels to prevent deadlocks
- Range loops over channels

## Running the Sample

```bash
go run sample.go
```

## Output

The program reports the status of each URL check, indicating whether each GitHub profile was successfully reached.
