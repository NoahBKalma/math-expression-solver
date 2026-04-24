# Math Expression Solver

This program solves math expressions for you.

## Usage    

### Requirements
- **Compiler (Able to run C++ 20):**
    - GCC 10+ (Tested with 13.2.0)
- **Optional**
  - CMake 3.5+ (Tested with 4.2)

### How To Build & Run
 
Clone the repository, then choose one of the following build methods:


#### Option 1: GCC (No CMake needed)
 
```
g++ -std=c++20 main.cpp Lexer.cpp Parser.cpp Evaluator.cpp -o math_expression_solver
./math_expression_solver
```
#### Option 2: CMake
 
```
cmake -B build
cmake --build build
./build/math_expression_solver
```

### Current Features
- **Operators:** +, -, *, /, ^, !
- **Functions:** sqrt, log, sin, cos, tan, csc, sec, cot
- **Parentheses/brackets:** (including (), [], {})
- Step-by-step solution of expression
- Implicit multiplication e.g. 2(3+4) -> 2*(3+4)
- Negative numbers
- Multi-digit and decimal numbers
- Expression history with view/clear
- Interactive console-based menu

### Commands (Not case-sensitive)

- **Expression:** Allows user to enter expression
- **List:** Displays a list of commands
- **ShowH:** Shows history
- **ClearH:** Clears history
- **Clear:** Clears console
- **Exit:** Exits program (or enter expression prompt)

### Planned Features
- Support for full equations with multiple variables (hopefully)