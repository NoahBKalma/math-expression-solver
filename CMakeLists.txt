cmake_minimum_required(VERSION 4.2)
project(math_expression_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(math_expression_solver main.cpp
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
        Node.h
        Evaluator.cpp
        Evaluator.h
)
