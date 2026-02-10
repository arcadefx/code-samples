# Command Dispatcher

A demonstration of the command dispatcher pattern with role-based access control (RBAC) in Go.

## What It Does

Implements a dynamic command routing system that:
- Maps command strings to handler functions using a function map
- Enforces role-based permissions before executing commands
- Processes messages with commands based on user roles

## Key Concepts Demonstrated

- **Function maps** (`map[string]func()`) for dynamic dispatch
- **Role-based access control** using permission maps
- **Dynamic function invocation** based on string commands
- Error handling for unauthorized commands

## Roles and Permissions

- **admin**: Can execute `ask`, `invisibility`, and `end` commands
- **user**: Can execute `ask` and `end` commands only

## Running the Sample

```bash
go run main.go
```

## Author

Paul Cardwell  
Date: 8/20/2024  
Copyright: (c) 2024
