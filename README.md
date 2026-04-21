# Math Expression Solver

This program solves math expressions for you.

## Usage (Windows)

### Requirements

- A C++20-compatible compiler (Like GCC 10+)
- Windows

### How To Run

Run **calculator.exe** to run the program in a console.<br><br>
I created the .exe with the following GCC command:

```
g++ -std=c++20 main.cpp Lexer.cpp Parser.cpp Evaluator.cpp -o calculator.exe
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
