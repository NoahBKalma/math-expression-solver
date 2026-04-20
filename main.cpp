#include <iostream>

#include "Evaluator.h"


int main() {

    Evaluator evaluator{ "10*10^3" };
    std::cout << evaluator.evaluate();


    return 0;
}