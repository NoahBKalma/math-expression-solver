#include <cmath>
#include <iostream>

#include "Evaluator.h"


double Evaluator::evaluateFactorial(double n) { return tgamma(n + 1); }
double Evaluator::evaluateExponent(double n1, double n2) { return std::pow(n1, n2); }
double Evaluator::evaluateMultiply(double n1, double n2) { return n1 * n2; }
double Evaluator::evaluateDivide(double n1, double n2) { return (n2 != 0.0) ? n1/n2 : throw std::runtime_error("Cannot divide by 0"); }
double Evaluator::evaluateAdd(double n1, double n2) { return n1 + n2; }
double Evaluator::evaluateSubtract(double n1, double n2) { return n1 - n2; }

int Evaluator::findASTDepth_(const Node *base, int depth) {
    if(!base) return depth;
    depth++;

    int maxLeftDepth = findASTDepth_(base->leftNode.get(), depth);
    int maxRightDepth = findASTDepth_(base->rightNode.get(), depth);

    return std::max(maxLeftDepth, maxRightDepth);
}

void Evaluator::setExpression(const std::string& expression) {
    mExpressionParser.changeExpression(expression);
    mExpressionParser.parseExpression();
}

double Evaluator::evaluate() {
    // Print the initial step
    std::cout << "Step 1: "; mExpressionParser.printExpressionClean();
    // Find and store the depth of the tree
    maxASTDepth = findASTDepth();

    // Evaluate and store result in double result
    double result{ evaluate_(mExpressionParser.getRoot(), 0) };
    // Add successful calculation to history
    mHistory.emplace_back( mExpressionParser.getExpression(), result );
    return result;
}

double Evaluator::evaluate_(Node *base, int depth) {
    if(!base) throw std::runtime_error("Node is null in evaluate_()");

    // If at a leaf node (just a number), return the number
    if(base->token.mType == TokenType::Number) {
        return std::stod(base->token.mValue);
    }
    // If there'ss somehow another token in that isn't an operator, throw an error
    if(base->token.mType != TokenType::Operator) throw std::runtime_error("Unknown token: " + base->token.mValue);

    // Evaluates depending on what the base operator is
    // Also sets the operator node to equal the result of the operation (evaluating the tree upwards)
    depth++;
    if(base->token.mValue == "!") {
        base->token.mValue = std::to_string(evaluateFactorial(evaluate_(base->leftNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
    } if(base->token.mValue == "^") {
        base->token.mValue = std::to_string(evaluateExponent(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
        base->rightNode = nullptr;
    } if(base->token.mValue == "*") {
        base->token.mValue = std::to_string(evaluateMultiply(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
        base->rightNode = nullptr;
    } if(base->token.mValue == "/") {
        base->token.mValue = std::to_string(evaluateDivide(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
        base->rightNode = nullptr;
    } if(base->token.mValue == "+") {
        base->token.mValue = std::to_string(evaluateAdd(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
        base->rightNode = nullptr;
    } if(base->token.mValue == "-") {
        base->token.mValue = std::to_string(evaluateSubtract(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->leftNode = nullptr;
        base->rightNode = nullptr;
    }
    // Prints the current step (in reverse order, so subtract the step depth from tree depth)
    std::cout << "Step " << maxASTDepth - depth + 1 << ": ";
    mExpressionParser.printExpressionClean();
    return std::stod(base->token.mValue);
}

void Evaluator::printHistory() {
    // Print history if there is any
    if(mHistory.empty()) {
        std::cout << "History empty\n";
        return;
    }
    for(const auto&[first, second] : mHistory) {
        std::cout << first << ": " << second << std::endl;
    }
}
