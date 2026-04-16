#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string& inputString) {
    std::vector<Token> tokens;
    tokens.push_back(Token({inputString[0]}));

    // Skipping whitespace, each char is added as a token
    for(int i = 1; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;

        Token newToken { {inputString[i]} };
        // If the current token is a number and the previous one is a number, combine them to make a multi-digit number
        if(newToken.type == TokenType::Number && tokens.back().type == TokenType::Number) {
            tokens.back().value += newToken.value;
        } else {
            tokens.push_back(newToken);
        }
    }

    return tokens;
}