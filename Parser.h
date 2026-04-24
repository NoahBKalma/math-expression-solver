#pragma once

#include <vector>
#include <string>

#include "Lexer.h"
#include "Node.h"

class Parser {
private:
    std::string mExpression;
    std::vector<Token> mTokenizedExpression;
    std::unique_ptr<Node> mRoot;

    // Helper recursive function for parseExpression()
    void parseExpression_(std::vector<Token>, std::unique_ptr<Node>&);

    // Helper recursive function for printExpression()
    void printExpression_(const Node*, size_t) const;
    void printExpressionClean_(const Node*, const Node* parent) const;

    // Cleans expression (adds * before parenthesis, removes parentheses wrapping whole expression
    void cleanExpression(std::vector<Token>&);

    // Returns the first position of a token of the given type (returns -1 if not found)
    size_t findLowestPrecedence(const std::vector<Token>&) const;

    // Gets precedence of token in given node
    size_t getPrecedence(const Node*) const;

public:
    // Initializes the expression and then tokenizes it with the lexer to get the tokenized expression
    Parser(const std::string& expression) :
        mExpression{ expression },
        mTokenizedExpression{ Lexer::tokenize(expression) },
        mRoot{ nullptr } {}

    Parser() : mRoot{ nullptr } {}

    /* changeExpression allows you to change the expression used by the parser. */
    void changeExpression(const std::string&);
    const std::string& getExpression() { return mExpression; }

    // parseExpression generates a tree with member variable root as the root
    // Each child represents a token in the equation
    void parseExpression();

    // printExpression prints the expression from a tree. Used for testing
    void printExpression() const { printExpression_(mRoot.get(), 0); }
    void printExpressionClean() const { printExpressionClean_(mRoot.get(), nullptr); std::cout << std::endl; }

    // Return the root of the expression tree
    Node* getRoot() const { return mRoot.get(); }
};
