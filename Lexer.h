#pragma once

#include <vector>
#include <string>
#include "Token.h"

class Lexer {
private:
public:
    static std::vector<Token> tokenize(const std::string& inputString);

    static bool isWhitespace(char c) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f'); }
};