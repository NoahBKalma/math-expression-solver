#include <cmath>
#include <iostream>

#include "Evaluator.h"


double Evaluator::evaluateFactorial(double n) { return static_cast<double>(tgamma(n + 1)); }
double Evaluator::evaluateExponent(double n1, double n2) { return std::pow(n1, n2);}
double Evaluator::evaluateMultiply(double n1, double n2) { return n1 * n2; }
double Evaluator::evaluateDivide(double n1, double n2) { return (n2 != 0.0) ? n1/n2 : throw std::runtime_error("Cannot divide by 0"); }
double Evaluator::evaluateAdd(double n1, double n2) { return n1 + n2; }
double Evaluator::evaluateSubtract(double n1, double n2) { return n1 - n2; }

void Evaluator::setExpression(const std::string& expression) {
    mExpressionParser.changeExpression(expression);
    mExpressionParser.parseExpression();
}

double Evaluator::evaluate() {
    // Evaluate and store result in double result
    double result{ evaluate_(mExpressionParser.getRoot()) };
    // Add successful calculation to history
    mHistory.emplace_back( mExpressionParser.getExpression(), result );
    return result;
}

double Evaluator::evaluate_(const Node *base) {
    if(!base) throw std::runtime_error("Node is null in evaluate_()");

    // If at a leaf node (just a number), return the number
    if(base->token.mType == TokenType::Number) {
        return std::stod(base->token.mValue);
    }
    // If theres somehow another token in that isn't an operator, throw an error
    if(base->token.mType != TokenType::Operator) throw std::runtime_error("Unknown token: " + base->token.mValue);

    // Evaluates depending on what the base operator is
    if(base->token.mValue == "!") {
        return evaluateFactorial(evaluate_(base->leftNode.get()));
    } if(base->token.mValue == "^") {
        return evaluateExponent(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } if(base->token.mValue == "*") {
        return evaluateMultiply(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } if(base->token.mValue == "/") {
        return evaluateDivide(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } if(base->token.mValue == "+") {
        return evaluateAdd(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } if(base->token.mValue == "-") {
        return evaluateSubtract(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    }
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
