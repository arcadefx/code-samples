# OOP-like Patterns in Go

This project demonstrates object-oriented programming patterns in Go using interfaces and structs.

## What It Does

Implements a simple grocery bag system that:
- Creates grocery bags with items
- Adds items to bags
- Displays bag contents with costs
- Uses interfaces for abstraction

## Key Concepts Demonstrated

- **Interfaces** for defining contracts (`Bag` interface)
- **Structs** for data modeling (`Item`, `GroceryBag`)
- **Constructor pattern** with `NewBag()` factory function
- **Method receivers** on structs
- **Encapsulation** of behavior

## Project Structure

```
oop-like/
├── main.go              # Entry point
├── grocerybag/
│   └── grocerybag.go   # Bag interface and implementation
└── go.mod
```

## Running the Sample

```bash
go run main.go
```

## Output

Displays the contents and total cost of grocery bags as items are added.
