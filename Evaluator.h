#pragma once

#include "Parser.h"
#include "Node.h"

class Evaluator {
private:
    Parser expressionParser;

    // Helper recursive function for evaluate()
    float evaluate_(Node*);

    // Evaluates an expression without sub-expressions
    float evaluateSimplifiedExpression(std::vector<Token>& tokenExpression);

    // Evaluates 2 numbers with a given operator
    float evaluateFactorial(float);
    float evaluateExponent(float, float);
    float evaluateMultiplyDivide(float, Token&, float);
    float evaluateAddSubtract(float, Token&, float);

    // Helper recursive function for cleanTokenExpression()
    void cleanTokenExpression_(Node*);

public:
    // This sets up the expression using the expression parser
    void setExpression(const std::string&);

    // This cleans up the tokens to include * where it may be implied to people
    void cleanTokenExpression() { cleanTokenExpression_(expressionParser.getRoot()); }

    // This is the bulk of the code, actually evaluates expressions
    float evaluate();

    // Print tree structure using parser print function (for testing purposes)
    void print() { expressionParser.printExpression(); }
};