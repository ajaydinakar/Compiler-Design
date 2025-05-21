# Compiler-Design
Project to design a compiler for a sample language


---

# L756 Language Scanner: Code Explanation

## Overview

This document explains a C++ program that implements a **scanner (lexical analyzer)** for the custom programming language **L756**. Developed for a compiler course assignment, its purpose is to process input source code, identify tokens (such as identifiers, numbers, and operators), and output their classes and values for subsequent compilation stages.

---

## Purpose

- **Input:**  
  - Source code in the L756 language.
  - Supporting files:  
    - `sy.txt` — Symbol/reserved word table  
    - `sc.txt` — Scanner state transition table

- **Output:**  
  - A file listing recognized tokens, their classes, and values.

---

## Major Components

### 1. Global Variables & Data Structures

- `symtab[100][3]`: Symbol table for reserved words and identifiers.
- `inttab[100][2]`: Table for integer constants.
- `M[13][13]`: State transition table for the scanner’s finite automaton.
- Other variables handle input, output, and scanning state.

---

### 2. Program Flow

#### Initialization

- User is prompted for the input and output file names.
- Tables are initialized via `initialize_Tables()`, which loads:
  - Reserved words (`sy.txt`)
  - Scanner states (`sc.txt`)

#### Main Scanning Loop

- The program reads the input file.
- It repeatedly calls `SCANTOKEN()` to extract tokens until reaching the end of the file.
- Recognized tokens and their classifications are output to both the console and the output file.

---

### 3. Token Scanning Logic

#### `SCANTOKEN()`

- Implements the **scanner’s finite state machine**.
- Reads characters using `NEXTCHAR()`.
- Utilizes the state transition table `M` to move between states.
- When a final (negative) state is reached, calls `Action()` to process the token.

#### `NEXTCHAR()`

- Reads the next character from the input file.
- Loads new lines as needed.

#### `scanTabindex()`

- Maps input characters to columns in the state transition table, categorizing them (e.g., digit, letter, operator).

#### `Action()`

- Interprets the final state to determine the token class and value.
- Handles output and error reporting.

#### `LOOKID()` and `LOOKINT()`

- `LOOKID()`: Checks if an identifier exists in the symbol table, adds it if not.
- `LOOKINT()`: Checks if an integer value exists in the integer table, adds it if not.

---

### 4. Table Initialization

#### `initialize_Tables()`

- Loads reserved words and states from `sy.txt` and `sc.txt`.
- Initializes the tables for symbols and integers.
- Populates the state transition table for the scanner.

---

### 5. Error Handling

#### `ERROR()`

- Outputs an error message to the output file for invalid characters.

---

## Example Workflow

1. The user runs the program and provides the input and output file names.
2. The program loads all necessary tables from external files.
3. The scanner reads input one character at a time, grouping them into tokens using the state transition table.
4. Upon recognizing a token, it is classified and outputted.
5. The process repeats until end-of-file.

---

## Key Features

- **Table-driven design**: Uses a state machine defined by an external matrix (`M`).
- **Token recognition**: Based on state transitions and action codes.
- **Symbol and integer tables**: Track identifiers and integer literals.
- **Configurable**: The logic can be adapted for more complex token sets by modifying the input files.

---

## Summary

This program is a practical example of a **lexical analyzer for the L756 language**. It employs a finite state machine, symbol and integer tables, and file-based configuration for flexibility and extensibility. It forms the first stage of a compiler for the L756 language.

---

