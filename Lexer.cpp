#include <algorithm>
#include <stdexcept>

#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string& inputString) {
    std::vector<Token> tokens;
    if(inputString.length() == 0) throw std::runtime_error("Empty expression");

    // Skipping whitespace, each char is added as a token
    for(int i = 0; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;

        Token newToken { {inputString[i]} };
        // If the current token is a number and the previous one is a number, combine them to make a multi-digit number
        if( newToken.mType == TokenType::Number &&
            !tokens.empty() &&
            tokens.back().mType == TokenType::Number) {

            tokens.back().mValue += newToken.mValue;
            if(std::ranges::count(tokens.back().mValue, '.') == 2)
                throw std::runtime_error("Two decimals in " + tokens.back().mValue);
        } else {
            tokens.push_back(newToken);
        }
    }

    return tokens;
}
