#include <cmath>
#include <iostream>

#include "Evaluator.h"

float Evaluator::evaluateFactorial(float n) { return static_cast<float>(tgamma(n + 1)); }
float Evaluator::evaluateExponent(float n1, float n2) { return std::pow(n1, n2);}
float Evaluator::evaluateMultiply(float n1, float n2) { return n1 * n2; }
float Evaluator::evaluateDivide(float n1, float n2) { return (n2 != 0.0f) ? n1/n2 : throw std::runtime_error("Cannot divide by 0"); }
float Evaluator::evaluateAdd(float n1, float n2) { return n1 + n2; }
float Evaluator::evaluateSubtract(float n1, float n2) { return n1 - n2; }

void Evaluator::setExpression(const std::string& expression) {
    mExpressionParser.changeExpression(expression);
    mExpressionParser.parseExpression();
}

float Evaluator::evaluate() {
    float result{ evaluate_(mExpressionParser.getRoot()) };
    mHistory.emplace_back( mExpressionParser.getExpression(), result );
    return result;
}

float Evaluator::evaluate_(const Node *base) {
    if(!base) throw std::runtime_error("Node is null in evaluate_()");

    if(base->token.mType == TokenType::Number) {
        return std::stof(base->token.mValue);
    }
    if(base->token.mType != TokenType::Operator) throw std::runtime_error("Error evaluating expression");

    if(base->token.mValue == "!") {
        return evaluateFactorial(evaluate_(base->leftNode.get()));
    } else if(base->token.mValue == "^") {
        return evaluateExponent(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } else if(base->token.mValue == "*") {
        return evaluateMultiply(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } else if(base->token.mValue == "/") {
        return evaluateDivide(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } else if(base->token.mValue == "+") {
        return evaluateAdd(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    } else if(base->token.mValue == "-") {
        return evaluateSubtract(evaluate_(base->leftNode.get()), evaluate_(base->rightNode.get()));
    }
    return std::stof(base->token.mValue);
}

void Evaluator::printHistory() {
    if(mHistory.empty()) {
        std::cout << "History empty\n";
        return;
    }
    for(const auto&[first, second] : mHistory) {
        std::cout << first << ": " << second << std::endl;
    }
}
