#pragma once

#include <vector>
#include <string>

#include "Lexer.h"
#include "Node.h"

class Parser {
private:
    std::string expression;
    std::vector<Token> tokenizedExpression;
    std::unique_ptr<Node> root;

    // Helper recursive function for parseExpression()
    std::unique_ptr<Node> parseExpression_(const std::vector<Token>&);

    // Helper recursive function for printExpression()
    void printExpression_(const Node*, int) const;

public:
    // Initializes the expression and then tokenizes it with the lexer to get the tokenized expression
    Parser(const std::string& expression) :
        expression{ expression },
        tokenizedExpression{ Lexer::tokenize(expression) },
        root{ nullptr } {}

    Parser() : root{ nullptr } {}

    /* changeExpression allows you to change the expression used by the parser. */
    void changeExpression(const std::string&);

    // parseExpression generates a tree with member variable root as the root
    // Each child represents a sub-expression (separated with delimiters such as brackets)
    void parseExpression();

    // printExpression prints the tree structure of the expression. Used for testing
    void printExpression() const { printExpression_(root.get(), 0); }

    // Return the root of the expression tree
    Node* getRoot() const { return root.get(); }

    // Returns the first position of a token of the given type (returns -1 if not found)
    int find(TokenType, Node*);

    bool contains(TokenType, Node*);
};
