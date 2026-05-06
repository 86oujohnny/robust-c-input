# robust-c-input

A minimal C library for safe and validated user input.

---

## Overview

This project provides safer alternatives to common input functions such as `get_int` and `get_string`, with proper validation and error handling.

It is designed to handle common edge cases in user input, including invalid characters, overflow, and incomplete input.

---

## Features

- Safe integer parsing using `strtol`
- Full input validation (invalid input, overflow, extra characters)
- Protection against buffer overflow
- Retry loop for user-friendly CLI input
- Dynamic string input using `getline`

---

## Functions

### `int get_int(const char *prompt)`

Prompts the user for an integer and ensures:

- Input is a valid number
- No extra characters are present
- Value is within `int` range
- Retries until valid input is given

---

### `char *get_string(const char *prompt)`

Prompts the user for a string:

- Reads a full line safely using `getline`
- Removes trailing newline
- Returns a dynamically allocated string (must be freed by the caller)

---

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int main(void)
{
    char *name = get_string("Name: ");
    if (!name) return 1;

    printf("Hello, %s\n", name);
    free(name);

    int age = get_int("Age: ");
    printf("Age = %d\n", age);

    return 0;
}
```
## Memory Management

`get_string` returns a heap-allocated string.

The caller is responsible for freeing the allocated memory to avoid memory leaks:

```c
free(name);
```
## Build
gcc cs50note.c -o program
## Motivation

This project was created to build a robust and reusable input system in C, focusing on correctness, safety, and clarity beyond basic examples.

## Author

Tzung-Lin Ou