#include <iostream>
#include "Token.h"
#include "Lexer.h"

int main() {
    for(const Token& currToken : Lexer::tokenize("342-12'103^3+5")) {
        std::cout << currToken.value << ", ";
    }

    return 0;
}