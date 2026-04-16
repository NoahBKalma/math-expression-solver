#include <cmath>

#include "Evaluator.h"

void Evaluator::setExpression(const std::string& expression) {
    expressionParser.changeExpression(expression);
    expressionParser.parseExpression();
}

void Evaluator::cleanTokenExpression_(Node* base) {
    for(int i = 1; i < base->tokens.size() - 1; i++) {
        if(base->tokens[i].type != TokenType::SubExpression) continue;
        if( (base->tokens[i-1].type == TokenType::Number) ||
            (base->tokens[i-1].type == TokenType::SubExpression)) {

            base->tokens.insert(base->tokens.begin() + i, Token{"*"});
            i++;
        }
        if( (i + 1 < base->tokens.size()) &&
            (base->tokens[i+1].type == TokenType::Number ||
            base->tokens[i+1].type == TokenType::SubExpression)) {

            base->tokens.insert(base->tokens.begin()+i+1, Token{"*"});
        }
    }

    for(std::unique_ptr<Node>& child : base->children) {
        cleanTokenExpression_(child.get());
    }
}

float Evaluator::evaluate() {
    if(!expressionParser.getRoot()) throw std::runtime_error("No expression loaded into evaluator");
    return evaluate_(expressionParser.getRoot());
}

float Evaluator::evaluateFactorial(float num) {
    return std::tgamma(num+1); }
float Evaluator::evaluateExponent(float num1, float num2) {
    return std::pow(num1, num2); }
float Evaluator::evaluateMultiplyDivide(float num1, Token& operatorToken, float num2) {
    if(operatorToken.value == "/") {
        if(num2 == 0.0f) throw std::runtime_error("Cannot divide by 0");
        return num1 / num2;
    }
    return num1 * num2;
}
float Evaluator::evaluateAddSubtract(float num1, Token& operatorToken, float num2) {
    return (operatorToken.value == "+") ? num1 + num2 : num1 - num2; }


float Evaluator::evaluate_(Node *base) {

    // Logic to recursively get rid of and evaluate sub-expressions
    int subExprCount{ 0 };
    int subExprLocation{ expressionParser.find(TokenType::SubExpression, base) };
    while(subExprLocation > -1) {
        base->tokens[subExprLocation].f_value = evaluate_(base->children[subExprCount].get());
        base->tokens[subExprLocation].type = TokenType::Number;
        subExprCount++;
        subExprLocation = expressionParser.find(TokenType::SubExpression, base);
    }
    return evaluateSimplifiedExpression(base->tokens);
}

float Evaluator::evaluateSimplifiedExpression(std::vector<Token>& tokenExpression) {
    // Logic to evaluate simplified expression without sub-expressions
    for(int i = 0; i < 4; i++) {
        // Only token types left are Number and Operator
        switch(i) {
            case 0:
                for(int j = tokenExpression.size()-1; j >= 0; j--) {
                    if(tokenExpression[j].type == TokenType::Number) continue;
                    if(tokenExpression[j].value != "!") continue;
                    tokenExpression[j-1].f_value = evaluateFactorial(tokenExpression[j-1].f_value);
                    tokenExpression.erase(tokenExpression.begin()+j, tokenExpression.begin()+j+1);
                }
                break;
            case 1:
                for(int j = tokenExpression.size()-1; j >= 0; j--) {
                    if(tokenExpression[j].type == TokenType::Number) continue;
                    if(tokenExpression[j].value != "^") continue;
                    tokenExpression[j-1].f_value = evaluateExponent(tokenExpression[j-1].f_value, tokenExpression[j+1].f_value);
                    tokenExpression.erase(tokenExpression.begin()+j, tokenExpression.begin()+j+2);
                }
                break;
            case 2:
                for(int j = 0; j < tokenExpression.size(); j++) {
                    if(tokenExpression[j].type == TokenType::Number) continue;
                    if(tokenExpression[j].value != "*" && tokenExpression[j].value != "/") continue;
                    tokenExpression[j-1].f_value = evaluateMultiplyDivide(tokenExpression[j-1].f_value, tokenExpression[j], tokenExpression[j+1].f_value);
                    tokenExpression.erase(tokenExpression.begin()+j, tokenExpression.begin()+j+2);
                    j--;
                }
                break;
            case 3:
                for(int j = 0; j < tokenExpression.size(); j++) {
                    if(tokenExpression[j].type == TokenType::Number) continue;
                    if(tokenExpression[j].value != "+" && tokenExpression[j].value != "-") continue;
                    tokenExpression[j-1].f_value = evaluateAddSubtract(tokenExpression[j-1].f_value, tokenExpression[j], tokenExpression[j+1].f_value);
                    tokenExpression.erase(tokenExpression.begin()+j, tokenExpression.begin()+j+2);
                    j--;
                }
                break;
        }
    }

    return tokenExpression[0].f_value;
}

