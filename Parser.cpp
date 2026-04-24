#include <vector>
#include <iostream>
#include <cmath>

#include "Parser.h"
#include "Lexer.h"

size_t Parser::getPrecedence(const Node* node) const {
    if(!node) return SIZE_MAX;
    if(node->token.mType == TokenType::Function) return 5;
    if(node->token.mValue == "!") return 4;
    if(node->token.mValue == "^") return 3;
    if(node->token.mValue == "*" || node->token.mValue == "/") return 2;
    if(node->token.mValue == "+" || node->token.mValue == "-") return 1;
    return SIZE_MAX;
}

void Parser::changeExpression(const std::string& expression) {
    // Sets the new expression and tokenized expression, then resets the root
    this->mExpression = expression;
    mTokenizedExpression = Lexer::tokenize(expression);
    mRoot = nullptr;
}

void Parser::parseExpression() {
    if(mRoot) return;
    parseExpression_(mTokenizedExpression, mRoot);
}

void Parser::parseExpression_(std::vector<Token> tokenExpression, std::unique_ptr<Node>& base) {
    // Checks the expression is valid
    if(tokenExpression.empty()) throw std::runtime_error("Error parsing expression.");

    // Cleans Expression
    cleanExpression(tokenExpression);

    // If it's just one token (number left) then add it to list
    if(tokenExpression.size() <= 1) {
        if(tokenExpression[0].mType != TokenType::Number) throw std::runtime_error("Invalid token: " + tokenExpression[0].mValue);
        base = std::make_unique<Node>(tokenExpression[0]);
        return;
    }

    // Finds the lowest precedence operator to build the list from the top down
    size_t pos = findLowestPrecedence(tokenExpression);
    if(pos == SIZE_MAX) throw std::runtime_error("Error parsing expression");

    // Adds the operator to the tree and then recursively calls the left and right sides of the expression
    base = std::make_unique<Node>(tokenExpression[pos]);

    // Only uses the right side of the function call
    if(base->token.mType == TokenType::Function) {
        parseExpression_(std::vector<Token>{tokenExpression.begin() + pos + 1, tokenExpression.end()}, base->rightNode);
    // Because ! is unary, it only parses what is to the left of it
    } else if(base->token.mValue == "!") {
        parseExpression_(std::vector<Token>{tokenExpression.begin(), tokenExpression.begin() + pos}, base->leftNode);
    } else {
        parseExpression_(std::vector<Token>{tokenExpression.begin(), tokenExpression.begin() + pos}, base->leftNode);
        parseExpression_(std::vector<Token>{tokenExpression.begin() + pos + 1, tokenExpression.end()}, base->rightNode);
    }
}

void Parser::printExpression_(const Node* base, size_t spaces) const {
    if(!base) return;

    // Increments depth for each level it parses
    spaces += 5;
    printExpression_(base->rightNode.get(), spaces);

    // Prints the value with appropriate spaces
    std::cout << std::endl;
    std::cout << std::string(spaces, ' ');
    std::cout << base->token.mValue;

    // Calls recursively going left
    printExpression_(base->leftNode.get(), spaces);
}

void Parser::printExpressionClean_(const Node *base, const Node *parent) const {
    if(!base) return;

    bool needsParenthesis;
    if(!parent) needsParenthesis = false;
    else needsParenthesis = base->token.mType == TokenType::Operator || // Puts parenthesis around operator nodes and children
                            parent->token.mType == TokenType::Function; // Puts paranthesis around things inside functions

    if(needsParenthesis) std::cout << "(";
    printExpressionClean_(base->leftNode.get(), base);
    if(base->token.mType == TokenType::Number) std::cout << std::round(std::stod(base->token.mValue)*10000)/10000;
    else std::cout << base->token.mValue;
    printExpressionClean_(base->rightNode.get(), base);
    if(needsParenthesis) std::cout << ")";
}

void Parser::cleanExpression(std::vector<Token>& tokenExpression) {
    if(tokenExpression[0].mType == TokenType::DelimiterClose) throw std::runtime_error("First token cannot be " + tokenExpression[0].mValue);

    while(tokenExpression[0].mType == TokenType::DelimiterOpen) {
        // If there are delimiters wrapping the whole expression, remove them
        int depth{ 0 };
        bool wrapped{ tokenExpression.front().mType == TokenType::DelimiterOpen };
        for(int i = 0; i < tokenExpression.size(); i++) {
            // Also check for errors in delimiters (not matching)
            if(tokenExpression[i].mType == TokenType::DelimiterOpen) depth++;
            else if(tokenExpression[i].mType == TokenType::DelimiterClose) depth--;
            if(depth == 0 && i != tokenExpression.size()-1) wrapped = false;
            if(depth < 0 || (depth > 0 && i == tokenExpression.size()-1)) throw std::runtime_error("Number of opening and closing brackets don't match.");
        }
        // If the expression is wrapped, remove beginning and ending delimiters
        if(!wrapped) break;

        tokenExpression.erase(tokenExpression.end()-1);
        tokenExpression.erase(tokenExpression.begin());
        if(tokenExpression.empty()) throw std::runtime_error("Expression is empty.");
    }

    if(tokenExpression[0].mValue == "-") tokenExpression.emplace(tokenExpression.begin(), Token{"0"});
    for(int i = 0; i < tokenExpression.size(); i++) {
        // Add implicit multiplication (before delimiters) and fix negatives
        if((tokenExpression[i].mType == TokenType::DelimiterOpen &&  // Checks to add implicit multiplication before a delimiter
                i > 0 &&
                (tokenExpression[i-1].mType == TokenType::Number ||
                tokenExpression[i-1].mType == TokenType::DelimiterClose))) {
            tokenExpression.emplace(tokenExpression.begin() + i, Token("*"));
            i++;
        } else if((tokenExpression[i].mType == TokenType::Number && // Checks to add implicit multiplication before a number
                i > 0 &&
                tokenExpression[i-1].mType == TokenType::DelimiterClose)) {
            tokenExpression.emplace(tokenExpression.begin() + i, Token("*"));
            i++;
        } else if((tokenExpression[i].mType == TokenType::Function && // Checks to add implicit multiplication before a function
                i > 0 &&
                (tokenExpression[i-1].mType == TokenType::Number ||
                tokenExpression[i-1].mType == TokenType::DelimiterClose))) {
            tokenExpression.emplace(tokenExpression.begin() + i, Token("*"));
            i++;
        } else if(tokenExpression[i].mType == TokenType::Number &&  // Checks and fixes negatives
                i >= 2 &&
                tokenExpression[i-1].mValue == "-" &&
                (tokenExpression[i-2].mType == TokenType::DelimiterOpen ||
                tokenExpression[i-2].mType == TokenType::Operator)) {
            tokenExpression.emplace(tokenExpression.begin() + i - 1, Token("0"));
            tokenExpression.emplace(tokenExpression.begin() + i - 1, Token("("));
            tokenExpression.emplace(tokenExpression.begin() + i + 3, Token(")"));
            i += 4;
        }
    }
}

size_t Parser::findLowestPrecedence(const std::vector<Token>& tokenExpression) const {
    // Precedence and precedence index tracking, also depth tracking for delimiters
    size_t posLowestPrecedence{ SIZE_MAX };
    int lowestPrecedence{ INT_MAX }, depth{ 0 };
    for(int i = 0; i < tokenExpression.size(); i++) {
        // Depth tracking
        if(tokenExpression[i].mType == TokenType::DelimiterOpen || tokenExpression[i].mType == TokenType::DelimiterClose) {
            if(tokenExpression[i].mType == TokenType::DelimiterOpen) depth++;
            else depth--;
        }
        // Only checks token if it is an operator or function
        if(tokenExpression[i].mType != TokenType::Operator && tokenExpression[i].mType != TokenType::Function) continue;

        // Doesn't check for precedence within delimiters
        if(depth > 0) continue;

        // Sets lowest precedence and its position for each operator
        // Everything except ^ is >= to give leftmost precedence for operators with equivalent precedence (^ is rightmost)
        if(tokenExpression[i].mType == TokenType::Function && lowestPrecedence >= 5) {
            lowestPrecedence = 5;
            posLowestPrecedence = i;
        } else if(tokenExpression[i].mValue == "!" && lowestPrecedence >= 4) {
            lowestPrecedence = 4;
            posLowestPrecedence = i;
        } else if(tokenExpression[i].mValue == "^" && lowestPrecedence > 3) {
            lowestPrecedence = 3;
            posLowestPrecedence = i;
        } else if((tokenExpression[i].mValue == "*" || tokenExpression[i].mValue == "/") && lowestPrecedence >= 2) {
            lowestPrecedence = 2;
            posLowestPrecedence = i;
        } else if((tokenExpression[i].mValue == "+" || tokenExpression[i].mValue == "-") && lowestPrecedence >= 1) {
            lowestPrecedence = 1;
            posLowestPrecedence = i;
        }
    }

    return posLowestPrecedence;
}
