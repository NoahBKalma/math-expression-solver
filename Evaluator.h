#pragma once

#include "Parser.h"
#include "Node.h"

class Evaluator {
private:
    Parser mExpressionParser;
    std::vector<std::pair<std::string, double>> mHistory;
    size_t maxASTDepth;
    bool evaluated;

    // Helper recursive function for evaluate()
    double evaluate_(Node*, size_t);

    // Evaluate with unary and binary operators
    static double evaluateFactorial(double);
    static double evaluateExponent(double, double);
    static double evaluateMultiply(double, double);
    static double evaluateDivide(double, double);
    static double evaluateAdd(double, double);
    static double evaluateSubtract(double, double);
    static double evaluateFunction(std::string, double);

    // Find max depth
    size_t findASTDepth_(const Node*, size_t);
    size_t findASTDepth() { return findASTDepth_(mExpressionParser.getRoot(), 0); }

public:
    // Constructor
    Evaluator(const std::string& expressionInput) : mExpressionParser{ expressionInput } { mExpressionParser.parseExpression(); }
    Evaluator() = default;

    // This sets up the expression using the expression parser
    void setExpression(const std::string&);
    const std::string& getExpression() { return mExpressionParser.getExpression(); }

    // This is the bulk of the code, actually evaluates expressions
    double evaluate();

    // Print tree structure using parser print function (for testing purposes)
    void print() { mExpressionParser.printExpression(); }

    // Manage History
    void printHistory();
    void clearHistory() { mHistory.clear(); }
};