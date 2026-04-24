#include <cmath>
#include <iostream>

#include "Evaluator.h"


double Evaluator::evaluateFactorial(double n) { return tgamma(n + 1); }
double Evaluator::evaluateExponent(double n1, double n2) { return std::pow(n1, n2); }
double Evaluator::evaluateMultiply(double n1, double n2) { return n1 * n2; }
double Evaluator::evaluateDivide(double n1, double n2) { return (n2 != 0.0) ? n1/n2 : throw std::runtime_error("Cannot divide by 0"); }
double Evaluator::evaluateAdd(double n1, double n2) { return n1 + n2; }
double Evaluator::evaluateSubtract(double n1, double n2) { return n1 - n2; }
double Evaluator::evaluateFunction(std::string func, double n1) {
    if(func == "sqrt") {
        return std::sqrt(n1);
    } if(func == "log") {
        return std::log(n1);
    } if(func == "sin") {
        return std::sin(n1 * M_PI/180);
    } if(func == "cos") {
        return std::cos(n1 * M_PI/180);
    } if(func == "tan") {
        return std::tan(n1 * M_PI/180);
    } if(func == "csc") {
        return 1/std::sin(n1 * M_PI/180);
    } if(func == "sec") {
        return 1/std::cos(n1 * M_PI/180);
    } if(func == "cot") {
        return 1/std::tan(n1 * M_PI/180);
    }
    throw std::runtime_error("Couldn't evaluate function " + func);
}

size_t Evaluator::findASTDepth_(const Node *base, size_t depth) {
    // If the base is empty, its parent is a leaf so just return depth
    if(!base) return depth;
    depth++;

    // After incrementing depth, recurse into children
    int maxLeftDepth = findASTDepth_(base->leftNode.get(), depth);
    int maxRightDepth = findASTDepth_(base->rightNode.get(), depth);

    // Return the max depth out of the two children
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

double Evaluator::evaluate_(Node *base, size_t depth) {
    if(!base) throw std::runtime_error("Node is null in evaluate_()");

    // If at a leaf node (just a number), return the number
    if(base->token.mType == TokenType::Number) {
        return std::stod(base->token.mValue);
    }
    // If there's somehow another token in that isn't an operator or function, throw an error
    if(base->token.mType != TokenType::Operator &&
     base->token.mType != TokenType::Function) throw std::runtime_error("Unknown token: " + base->token.mValue);

    // Evaluates depending on what the base operator is
    // Also sets the operator node to equal the result of the operation (evaluating the tree upwards)
    depth++;
    if(base->token.mType == TokenType::Function) {
        base->token.mValue = std::to_string(evaluateFunction(base->token.mValue, evaluate_(base->rightNode.get(), depth)));
        base->token.mType =TokenType::Number;
        base->removeRight();
    } if(base->token.mValue == "!") {
        base->token.mValue = std::to_string(evaluateFactorial(evaluate_(base->leftNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
    } if(base->token.mValue == "^") {
        base->token.mValue = std::to_string(evaluateExponent(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
        base->removeRight();
    } if(base->token.mValue == "*") {
        base->token.mValue = std::to_string(evaluateMultiply(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
        base->removeRight();
    } if(base->token.mValue == "/") {
        base->token.mValue = std::to_string(evaluateDivide(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
        base->removeRight();
    } if(base->token.mValue == "+") {
        base->token.mValue = std::to_string(evaluateAdd(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
        base->removeRight();
    } if(base->token.mValue == "-") {
        base->token.mValue = std::to_string(evaluateSubtract(evaluate_(base->leftNode.get(), depth), evaluate_(base->rightNode.get(), depth)));
        base->token.mType = TokenType::Number;
        base->removeLeft();
        base->removeRight();
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
