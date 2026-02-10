# JavaScript Code Samples

This directory contains various JavaScript algorithm and data structure implementations. All files can be run using Node.js.

## Running the Files

To run any file, use:
```bash
node <filename>.js
```

For example:
```bash
node fib.js
```

## File Descriptions

### Data Structures

#### `linkedlist.js`
Implements a singly linked list with add and print operations. Demonstrates basic linked list traversal and maintains both root and tail pointers for efficient insertion.

**Run:** `node linkedlist.js`

#### `addTwoNumbersLinkedList.js`
Implements linked list operations and demonstrates adding two numbers represented as linked lists (similar to LeetCode problem). Includes forward and reverse printing capabilities.

**Run:** `node addTwoNumbersLinkedList.js`

#### `avl.js`
Implements an AVL tree (self-balancing binary search tree) with insertion and rotation operations (left-left, right-right, left-right, and right-left rotations).

**Run:** `node avl.js`

#### `tries.js`
Implements a Trie (prefix tree) data structure for efficient word storage and retrieval. Supports adding words, searching for words, and getting all stored words.

**Run:** `node tries.js`

### Algorithms - Sorting

#### `bubble-sort.js`
Demonstrates bubble sort algorithm with a simple array of numbers. Sorts in ascending order using nested loops.

**Run:** `node bubble-sort.js`

### Algorithms - Searching & Traversal

#### `breadthfirstsearch.js`
Implements breadth-first search (BFS) on a binary tree using a queue-based approach. Demonstrates level-order traversal.

**Run:** `node breadthfirstsearch.js`

#### `depthfirstsearch.js`
Implements depth-first search (DFS) on a binary search tree with in-order traversal (left-root-right).

**Run:** `node depthfirstsearch.js`

### Algorithms - Mathematical

#### `fib.js`
Generates Fibonacci sequence up to a specified length using iterative approach. Returns an array of Fibonacci numbers.

**Run:** `node fib.js`

#### `prime-numbers.js`
Identifies and prints prime numbers from an input array using trial division method.

**Run:** `node prime-numbers.js`

#### `pascaltri.js`
Generates a specific row of Pascal's Triangle using dynamic programming. Each row is calculated based on the previous row.

**Run:** `node pascaltri.js`

#### `pyramid.js`
Creates a text-based pyramid pattern of specified height using hash symbols (#) and spaces.

**Run:** `node pyramid.js`

### Algorithms - String Manipulation

#### `remove-vowels.js`
Removes all vowels (a, e, i, o, u) from a string and prints the result.

**Run:** `node remove-vowels.js`

#### `defang-ip.js`
Defangs an IP address by replacing dots with "[.]". Shows two approaches: using regex replace and manual iteration.

**Run:** `node defang-ip.js`

### Algorithms - Array Problems

#### `largest-range.js`
Finds the largest range of consecutive integers in an array. Sorts the array first, then finds the longest sequence.

**Run:** `node largest-range.js`

#### `riversizes.js`
Solves the "River Sizes" problem: given a 2D matrix of 1s and 0s (where 1s represent river parts), calculates the size of each connected river using depth-first search.

**Run:** `node riversizes.js`

### Bit Manipulation

#### `bit-operations.js`
Demonstrates bitwise operations for permission management:
- Setting flags using OR (`|`)
- Checking flags using AND (`&`)
- Unsetting flags using AND with NOT (`&~`)

**Run:** `node bit-operations.js`

#### `ham.js`
Calculates Hamming distance between two numbers by XORing them and counting the 1s in the binary representation.

**Run:** `node ham.js`

### Asynchronous JavaScript

#### `async-await-example.js`
Demonstrates modern async/await syntax for handling asynchronous operations. Shows how to chain promises sequentially and handle errors with try/catch.

**Run:** `node async-await-example.js`

## Prerequisites

- Node.js installed (any recent version should work)
- No external dependencies required - all files use vanilla JavaScript

## Notes

- Most files include sample input data hardcoded in the file
- Output is printed to the console using `console.log()`
- Some files contain commented-out alternative test cases that can be uncommented for different scenarios
