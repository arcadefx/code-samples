# Python Code Samples

This directory contains various Python algorithm implementations and basic programming demonstrations. These scripts showcase fundamental Python concepts, data structures, and algorithms.

## Running the Files

To run any file, use:
```bash
python <filename>.py
```

For example:
```bash
python fib.py
# or with Python 3 explicitly
python3 fib.py
```

## File Descriptions

### Core Demonstrations

#### `main.py`
Comprehensive demonstration file that imports the Demo class and showcases various Python features:
- Class instantiation and method calls
- Object inheritance with FooClass
- Array manipulation and iteration
- String operations and substring iteration
- Dictionary usage
- String formatting

**Run:** `python main.py`

#### `demo.py`
Demo class implementation featuring:
- Private variables (`__privNumber`, `__privCode`)
- Class methods for various operations
- Array operations with `xrange` for efficiency
- Conditional logic with break/elif statements
- Element array management

**Run:** `python demo.py` (Note: Defines class but doesn't execute; import in another file)

#### `demoClass.py`
Alternative Demo class implementation with similar functionality:
- Method examples (greetUser, add, countTo)
- Array iteration with break conditions
- Private variable demonstrations
- String splitting and array factory methods

**Run:** `python demoClass.py` (Note: Defines class but doesn't execute; import in another file)

### Mathematical Algorithms

#### `fib.py`
Generates Fibonacci sequence using iterative approach with efficient `xrange`. Calculates and prints Fibonacci numbers up to a specified maximum.

**Run:** `python fib.py`

#### `prime.py`
Finds and prints all prime numbers from 2 to 100 using trial division method. Uses nested loops to check divisibility.

**Run:** `python prime.py`

#### `clock.py`
Calculates the angle between hour and minute hands on a clock face. Given an hour and minute, computes the degree separation between the two hands.

**Run:** `python clock.py`

### Bit Manipulation

#### `bit.py`
Demonstrates bitwise operations and bit manipulation techniques:
- Left shift (`<<`) for multiplication by 2
- Right shift (`>>`) for division by 2
- Setting bits using OR (`|`)
- Removing bits using AND with NOT (`&~`)
- Checking if specific bits are set

Includes flag management example with read/write permissions.

**Run:** `python bit.py`

### Object-Oriented Programming

#### `simpleCart.py`
Implements a simple shopping cart system using object-oriented principles:
- CartDemo class with initialization
- Add items to cart
- Display cart contents and count
- Demonstrates basic list operations

**Run:** `python simpleCart.py`

## Prerequisites

- Python 3.x installed (also compatible with Python 2.7 via `from __future__ import print_function`)
- No external dependencies required - all files use standard Python library

## Python 3 Compatibility

All files are Python 3 compatible and ready to run.

## Key Concepts Demonstrated

- **Classes and OOP**: Multiple class examples with inheritance
- **Private variables**: Using double underscore prefix (`__variable`)
- **Bit manipulation**: Efficient mathematical operations using bitwise operators
- **Iteration**: Using `range()` for efficient loops
- **String operations**: Splitting, iteration, formatting
- **Data structures**: Lists, dictionaries, arrays
- **Control flow**: Loops, conditionals, break statements

## Notes

- Most files include hardcoded sample data for demonstration
- Output is printed to console using `print()` functions
- Files like `demo.py` and `demoClass.py` define classes but don't execute code directly - they're meant to be imported
