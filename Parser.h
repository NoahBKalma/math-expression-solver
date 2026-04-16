#pragma once

#include <vector>
#include <string>
#include "Lexer.h"
#include "Node.h"

class Parser {
private:
    std::string expression;
    std::vector<Token> tokenizedExpression;
    Node *root;

    std::unique_ptr<Node> parseExpression_(const std::vector<Token>&);

    void printExpression_(Node*, int);

public:
    Parser(const std::string& expression) :
        expression{ expression },
        tokenizedExpression{ Lexer::tokenize(expression) },
        root{ nullptr } {}

    ~Parser() { delete root; }

    void changeExpression(const std::string&);
    void parseExpression();
    void printExpression() { printExpression_(root, 0); }
};
