#include <iostream>

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

std::string toLower(std::string& string) {
    for(char& c : string) if(c >= 65 && c <= 90) c += 32;
    return string;
}

void listOptions() {
    std::cout << "----------------------------------------\n"
                 "\'Expression\' to evaluate expression.\n"
                 "\'List\' to list commands.\n"
                 "\'Exit\' at any point to exit.\n"
                 "\'Clear\' to clear screen.\n"
                 "\'ShowH\' to clear screen.\n"
                 "\'ClearH\' to clear history.\n"
                 "----------------------------------------\n";
}

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

int main() {
    Evaluator evaluator;
    listOptions();
    MenuChoice userChoice{ getUserChoice() };

    while(userChoice != MenuChoice::Exit) {
        switch(userChoice) {
            case MenuChoice::EvalExpression:
                if(!getUserExpression(evaluator)) break;
                try { std::cout << "Expression equals: " << evaluator.evaluate() << "\n"; }
                catch(std::runtime_error& error) { std::cout << error.what() << "\n"; }
                break;
            case MenuChoice::ListOptions:
                listOptions();
                break;
            case MenuChoice::ClearScreen:
                std::cout << "\033[3J\033[H\033[2J" << std::flush;
                break;
            case MenuChoice::ShowHistory:
                std::cout << "-----------------------------\n";
                std::cout << "Expression: Result\n";
                evaluator.printHistory();
                std::cout << "-----------------------------\n";
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