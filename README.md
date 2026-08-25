# Math Expression Solver

![Language](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Status](https://img.shields.io/badge/status-complete-brightgreen?style=flat-square)

A C++ math expression solver that parses and evaluates expressions via a hand-written lexer, recursive-descent parser, and AST evaluator — showing its work step by step instead of just returning a final number.

---

## Demo

```
Enter Expression: sqrt(16) + 2^3 * (5 - 1)

Step 1: sqrt(16)+((2^3)*(5-1))
Step 2: sqrt(16)+((2^3)*4)
Step 3: sqrt(16)+(8*4)
Step 4: sqrt(16)+32
Step 5: 4+32
Step 6: 36

Expression equals: 36
```

---

## Features

- **Operators:** `+`, `-`, `*`, `/`, `^`, `!`
- **Functions:** `sqrt`, `ln`, `sin`, `cos`, `tan`, `csc`, `sec`, `cot` (trig functions in degrees)
- **Parentheses/brackets:** `()`, `[]`, `{}`
- Step-by-step solution of every expression, evaluated in real order via a recursive AST walk
- Implicit multiplication, e.g. `2(3+4)` → `2*(3+4)`
- Negative numbers, multi-digit numbers, and decimals
- Expression history with view/clear
- Interactive console-based menu

---

## Tech Stack

- **Language:** C++20
- **Build:** CMake or plain g++, no external dependencies

---

## Running it locally

```bash
git clone https://github.com/NoahBKalma/math-expression-solver.git
cd math-expression-solver
```

**Option 1: g++ (no CMake needed)**
```bash
g++ -std=c++20 main.cpp Lexer.cpp Parser.cpp Evaluator.cpp -o math_expression_solver
./math_expression_solver
```

**Option 2: CMake**
```bash
cmake -B build
cmake --build build
./build/math_expression_solver
```

### Commands (not case-sensitive)

- **Expression** — enter an expression to evaluate
- **List** — show all commands
- **ShowH** — show expression history
- **ClearH** — clear history
- **Clear** — clear the console
- **Exit** — exit the program (or the expression prompt)