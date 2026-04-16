#pragma once

#include <vector>
#include <string>
#include "Token.h"

class Lexer {
private:
public:
    static std::vector<Token> tokenize(const std::string&);

    static bool isWhitespace(const char c) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f'); }
};