#include <iostream>

#include "Token.h"
#include "Parser.h"
#include "Evaluator.h"

int main() {

    Evaluator evaluator;
    evaluator.setExpression("3.14*3");
    evaluator.cleanTokenExpression();
    evaluator.print();
    std::cout << "\n\n" << evaluator.evaluate();

    return 0;
}