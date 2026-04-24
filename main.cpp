#include <iostream>
#include <cmath>

#include "Evaluator.h"

enum class MenuChoice {
    EvalExpression,
    ListOptions,
    Exit,
    ClearScreen,
    ShowHistory,
    ClearHistory,
    Unknown
};

// Converts a string to lowercase;
void toLower(std::string& string) {
    for(char& c : string) if(c >= 65 && c <= 90) c += 32;
}

// Clears the screen (uses ANSI Escape Sequences)
void clearScreen() {
    // \033[H   -> Move cursor to home
    // \033[2J  -> Clear visible screen (often scrolls text up)
    // \033[3J  -> Deletes history (ensure clearing the \033[2J may have mixed)
    std::cout << "\033[H\033[2J\033[3J" << std::flush;
}

// Lists all possible user commands
void listOptions() {
    std::cout << "----------------------------------------\n"
                 "\'Expression\' to evaluate expression.\n"
                 "\'List\' to list commands.\n"
                 "\'Exit\' at any point to exit.\n"
                 "\'Clear\' to clear screen.\n"
                 "\'ShowH\' to show history.\n"
                 "\'ClearH\' to clear history.\n"
                 "----------------------------------------\n";
}

// Prompts the user for input on what command they want to execute
MenuChoice getUserChoice() {
    std::string userChoiceStr;
    std::cout << "What would you like to do: ";
    std::getline(std::cin, userChoiceStr);
    toLower(userChoiceStr);
    if(userChoiceStr == "expression") return MenuChoice::EvalExpression;
    if(userChoiceStr == "list") return MenuChoice::ListOptions;
    if(userChoiceStr == "exit") return MenuChoice::Exit;
    if(userChoiceStr == "clear") return MenuChoice::ClearScreen;
    if(userChoiceStr == "showh") return MenuChoice::ShowHistory;
    if(userChoiceStr == "clearh") return MenuChoice::ClearHistory;
    return MenuChoice::Unknown;
}

// Prompts the user for input on what expression they want to evaluate
bool getUserExpression(Evaluator& evaluator) {
    std::string userExpression{};
    while(true) {
        try {
            std::cout << "Enter Expression: ";
            std::getline(std::cin, userExpression);
            toLower(userExpression);
            if(userExpression == "exit") break;
            evaluator.setExpression(userExpression);
            return true;
        } catch(std::runtime_error& error) {
            std::cout << error.what() << "\n";
        }
    }
    return false;
}

// Evaluates Expression
void evalExpression(Evaluator& evaluator) {
    try {
        double exprResult{ evaluator.evaluate() };
        std::cout << "\nExpression equals: " << std::round(exprResult*10000)/10000 << "\n";
    }
    catch(std::runtime_error& error) { std::cout << error.what() << "\n"; }
}

int main() {
    clearScreen();
    Evaluator evaluator;
    listOptions();
    MenuChoice userChoice{ getUserChoice() };

    // Loops through user menu choices
    while(userChoice != MenuChoice::Exit) {
        switch(userChoice) {
            case MenuChoice::EvalExpression:
                if(!getUserExpression(evaluator)) break;
                evalExpression(evaluator);
                std::cout << "----------------------------------------\n";
                break;
            case MenuChoice::ListOptions:
                listOptions();
                break;
            case MenuChoice::ClearScreen:
                clearScreen();
                break;
            case MenuChoice::ShowHistory:
                std::cout << "----------------------------------------\n";
                std::cout << "Expression: Result\n";
                evaluator.printHistory();
                std::cout << "----------------------------------------\n";
                break;
            case MenuChoice::ClearHistory:
                evaluator.clearHistory();
                std::cout << "History cleared.\n";
                break;
            case MenuChoice::Unknown:
                std::cout << "Invalid choice.\n";
                break;
        }
        userChoice = getUserChoice();
    }

    return 0;
}