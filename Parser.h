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

    // Helper recursive function for parseExpression()
    std::unique_ptr<Node> parseExpression_(const std::vector<Token>&);

    // Helper recursive function for printExpression()
    void printExpression_(Node*, int);

public:
    // Initializes the expression and then tokenizes it with the lexer to get the tokenized expression
    Parser(const std::string& expression) :
        expression{ expression },
        tokenizedExpression{ Lexer::tokenize(expression) },
        root{ nullptr } {}

    // Deletes the root. Deletes the entire tree because the children are std::unique_ptr
    ~Parser() { delete root; }

    /* changeExpression allows you to change the expression used by the parser. */
    void changeExpression(const std::string&);

    // parseExpression generates a tree with member variable root as the root
    // Each child represents a sub-expression (separated with delimiters such as brackets)
    void parseExpression();

    // printExpression prints the tree structure of the expression. Used for testing
    void printExpression() { printExpression_(root, 0); }
};
