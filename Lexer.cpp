#include <algorithm>
#include <stdexcept>

#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string& inputString) {
    std::vector<Token> tokens;
    if(inputString.length() == 0) throw std::runtime_error("Empty expression");

    for(int i = 0; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;
        tokens.push_back(Token({inputString[i]}));
        break;
    }

    // Skipping whitespace, each char is added as a token
    for(int i = 1; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;

        Token newToken { {inputString[i]} };
        // If the current token is a number and the previous one is a number, combine them to make a multi-digit number
        if(newToken.type == TokenType::Number && tokens.back().type == TokenType::Number) {
            tokens.back().value += newToken.value;
            if(std::count(tokens.back().value.begin(), tokens.back().value.end(), '.') == 2) throw std::runtime_error("Two decimals in " + tokens.back().value);
        } else {
            tokens.push_back(newToken);
        }
    }

    for(Token& currToken : tokens) {
        if(currToken.type == TokenType::Number) currToken.f_value = std::stof(currToken.value);
    }

    return tokens;
}
