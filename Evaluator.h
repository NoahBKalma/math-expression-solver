#pragma once

#include "Parser.h"
#include "Node.h"

class Evaluator {
private:
    Parser mExpressionParser;

    // Helper recursive function for evaluate()
    float evaluate_(Node*);

    // Evaluate with unary and binary operators
    static float evaluateFactorial(float);
    static float evaluateExponent(float, float);
    static float evaluateMultiply(float, float);
    static float evaluateDivide(float, float);
    static float evaluateAdd(float, float);
    static float evaluateSubtract(float, float);

public:
    // Constructor
    Evaluator(const std::string& expressionInput) : mExpressionParser{ expressionInput } { mExpressionParser.parseExpression(); }

    // This sets up the expression using the expression parser
    void setExpression(const std::string&);

    // This is the bulk of the code, actually evaluates expressions
    float evaluate();

    // Print tree structure using parser print function (for testing purposes)
    void print() { mExpressionParser.printExpression(); }
};