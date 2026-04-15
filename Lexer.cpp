#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string& inputString) {
    std::vector<Token> tokens;
    tokens.push_back(Token({inputString[0]}));
    for(int i = 1; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;
        Token newToken { {inputString[i]} };
        if(newToken.type == TokenType::Number && tokens.back().type == TokenType::Number) {
            tokens.back().value += newToken.value;
        } else {
            tokens.push_back(newToken);
        }
    }

    return tokens;
}