#include <algorithm>
#include <stdexcept>

#include "Lexer.h"
#include "Tokens.h"

std::vector<Token> Lexer::tokenize(const std::string& inputString) {
    std::vector<Token> tokens;
    if(inputString.length() == 0) throw std::runtime_error("Empty expression.");

    // Skipping whitespace, each char is added as a token
    for(size_t i = 0; i < inputString.length(); i++) {
        if(isWhitespace(inputString[i])) continue;

        Token newToken { {inputString[i]} };
        if( newToken.mType == TokenType::Number &&
            !tokens.empty() &&
            tokens.back().mType == TokenType::Number) {
        // If the current token is a number and the previous one is a number, combine them to make a multi-digit number
            tokens.back().mValue += newToken.mValue;
            if(std::ranges::count(tokens.back().mValue, '.') == 2)
                throw std::runtime_error("Two decimals in " + tokens.back().mValue);
        }
        else {
            tokens.push_back(newToken);
        }
    }

    // Turns groups of letters into functions
    std::string currLetterCluster{ "" };
    for(size_t i = 0; i < tokens.size(); i++) {
        if(tokens[i].mType == TokenType::Letter) {
            currLetterCluster += tokens[i].mValue;
            continue;
        }
        if(tokens[i].mType != TokenType::Letter && !currLetterCluster.empty()) {
            if(isFunction(currLetterCluster)) {
                size_t clusterLength{ currLetterCluster.length() };
                tokens[i-clusterLength].mType = TokenType::Function;
                tokens[i-clusterLength].mValue = currLetterCluster;
                tokens.erase(tokens.begin() + i - clusterLength + 1, tokens.begin() + i);
                i -= currLetterCluster.length();
            } else {
                throw std::runtime_error("Unknown function: " + currLetterCluster);
            }
            currLetterCluster = "";
        }
    }
    if(!currLetterCluster.empty()) {
        throw std::runtime_error("Unknown function: " + currLetterCluster);
    }

    return tokens;
}
