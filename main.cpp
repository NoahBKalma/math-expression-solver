#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main() {
    Parser parser{"342-12*[103^(15/3)]+(5^2)"};
    parser.parseExpression();
    parser.printExpression();

    return 0;
}