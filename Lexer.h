#pragma once

#include <vector>
#include <string>
#include "Token.h"

class Lexer {
private:
public:
    // Turns a string into a vector of tokens
    static std::vector<Token> tokenize(const std::string&);

    // Checks if a given constant c is whitespace
    static bool isWhitespace(const char c) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f'); }
};