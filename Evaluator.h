#pragma once

#include "Parser.h"
#include "Node.h"

class Evaluator {
private:
    Parser mExpressionParser;
    std::vector<std::pair<std::string, float>> mHistory;

    // Helper recursive function for evaluate()
    float evaluate_(const Node*);

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
    Evaluator() = default;

    // This sets up the expression using the expression parser
    void setExpression(const std::string&);
    const std::string& getExpression() { return mExpressionParser.getExpression(); }

    // This is the bulk of the code, actually evaluates expressions
    float evaluate();

    // Print tree structure using parser print function (for testing purposes)
    void print() { mExpressionParser.printExpression(); }

    // Print History
    void printHistory();
    void clearHistory() { mHistory.clear(); }
};