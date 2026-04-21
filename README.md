# Math Expression Solver

This program solves math expressions for you.

## Usage    

### Requirements
- **Compiler (Able to run C++ 20):**
    - GCC 10+ (Tested with 13.2.0)
    - CMake 4.0+ (Tested with 4.2)
- **OS:** Windows

### How To Build & Run
 
Clone the repository, then choose one of the following build methods:


#### Option 1: GCC
 
```
g++ -std=c++20 main.cpp Lexer.cpp Parser.cpp Evaluator.cpp -o math_expression_solver.exe
./math_expression_solver.exe
```
#### Option 2: CMake
 
```
cmake -B build
cmake --build build
./build/math_expression_solver.exe
```

### Current Features
- Operators: +, -, *, /, ^, !
- Parentheses/brackets (including (), [], {})
- Implicit multiplication, e.g. 2(3+4)
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
- Functions such as sqrt() as well as sin(x), cos(x), and other trig functions
- Optional step-by-step breakdown of each expression
- Support for full equations with multiple variables
- Load back to previous expressions through the history (possibly)
