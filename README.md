# Arbitrary Precision Calculator (APC)

APC is an Arbitrary Precision Calculator implemented in C, designed to perform arithmetic operations on integers of arbitrary size beyond the limitations of native data types using a doubly linked list.

## Project Status

✅ Project Completed

## Implemented Features

### ✅ Command-line Argument Validation

The program validates user input before performing any arithmetic operation by checking:

- Correct number of command-line arguments
- Supported arithmetic operators
- Valid integer operands
- Appropriate error messages for invalid input

### ✅ Operation Determination

The calculator automatically determines the appropriate arithmetic operation based on the operator and the signs of both operands.

### ✅ Operand Conversion

- Converts command-line integer operands into doubly linked lists.
- Ignores unnecessary leading zeros.
- Stores one digit per node.

### ✅ Result Sign Determination

Determines whether the final result is positive, negative, or zero before performing the arithmetic operation.

### ✅ Arithmetic Operations

Implemented support for:

- Addition
- Subtraction
- Multiplication
- Division

### ✅ Linked List Operations

Implemented all required doubly linked list operations including:

- Insert at beginning
- Insert at end
- Delete first node
- Delete complete list
- Print list
- Count nodes

## Current Progress

- ✅ Initial project structure
- ✅ Command-line argument validation
- ✅ Operation determination
- ✅ Linked list implementation
- ✅ Operand conversion to linked list
- ✅ Result sign determination
- ✅ Addition
- ✅ Subtraction
- ✅ Multiplication
- ✅ Division
- ✅ Project completed

## Features

- Perform arithmetic operations on arbitrarily large integers
- Supports positive and negative integers
- Uses doubly linked lists for number representation
- Dynamic memory allocation
- Modular project structure
- Command-line interface
- Implemented entirely in C

## Project Structure

```text
APC/
├── README.md
├── apc.h
├── main.c
├── validation.c
├── converter.c
├── list.c
├── operations.c
```

## Getting Started

### Compilation

```bash
gcc *.c -o apc
```

### Usage

```bash
./apc <operand1> <operator> <operand2>
```

### Examples

```bash
./apc 12345678901234567890 + 98765432109876543210
./apc 999999999999999999 - 123456789
./apc 12345 x 6789
./apc 999999999 / 12345
```

## Future Enhancements

- Modulus operation
- Exponentiation
- Decimal number support
- Interactive calculator mode
- Performance optimization
- Unit testing

## Author

**Aromal K S**