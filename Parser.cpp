#include <vector>
#include <queue>
#include <iostream>

#include "Parser.h"
#include "Lexer.h"

void Parser::changeExpression(const std::string& expression) {
    // Sets the new expression and tokenized expression, then resets the root
    this->expression = expression;
    tokenizedExpression = Lexer::tokenize(expression);
    root = nullptr;
}

void Parser::parseExpression() {
    if(root) throw std::runtime_error("Already Parsed");
    root = parseExpression_(tokenizedExpression);
}

std::unique_ptr<Node> Parser::parseExpression_(const std::vector<Token>& tokenExpression) {
    // Creates a node for the current part of the expression
    std::unique_ptr<Node> node = std::make_unique<Node>(std::vector<Token>{});

    // Checks the type of tokens and processes accordingly
    for(int i = 0; i < tokenExpression.size(); i++) {
        switch(tokenExpression[i].type) {
            case TokenType::Unknown:
                // Throws an error if the token is unknown
                throw std::runtime_error("Unknown token " + tokenExpression[i].value);
                break;
            case TokenType::DelimiterOpen: {
                // Checks and creates sub-expressions for each set of delimiters - ()[]{}
                node->tokens.emplace_back();
                int delimCloseIndex{ 0 }, depth{ 0 };
                // Finds the index of the closing delimiter
                for(int j = i+1; j < tokenExpression.size(); j++) {
                    if(tokenExpression[j].type == TokenType::DelimiterOpen) depth++;
                    else if(tokenExpression[j].type == TokenType::DelimiterClose) {
                        if(depth == 0) {
                            delimCloseIndex = j;
                            break;
                        }
                        depth--;
                    }
                }
                // Create the sub-expression and then place that as a child by parsing through it
                std::vector<Token> subExpression{tokenExpression.begin() + i + 1, tokenExpression.begin() + delimCloseIndex};
                node->children.emplace_back(parseExpression_(subExpression));
                i  = delimCloseIndex;
                break;
            }
            case TokenType::DelimiterClose:
                break;
            // Pushes numbers and operators straight into the parsed token expression
            case TokenType::Number:
                node->tokens.push_back(tokenExpression[i]);
                break;
            case TokenType::Operator:
                node->tokens.push_back(tokenExpression[i]);
                break;
        }
    }

    return node;
}

void Parser::printExpression_(const Node* base, int depth) const {
    // Prints current data and then calls recursively for each child (runs over whole tree)
    std::cout << std::string(depth, '-');
    for(const Token& currToken : base->tokens) {
        std::cout << currToken.value << ", ";
    }
    std::cout << "\n";
    for(const std::unique_ptr<Node>& child : base->children) {
        printExpression_(child.get(), depth+1);
    }
}

int Parser::find(TokenType type, Node* node) {
    for(int i = 0; i < node->tokens.size(); i++) {
        if(node->tokens[i].type == type) return i;
    }
    return -1;
}

bool Parser::contains(TokenType type, Node *node) {
    return (find(type, node) > -1) ? true : false;
}

