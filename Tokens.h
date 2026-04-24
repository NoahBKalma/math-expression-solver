#pragma once

#include <string>
#include<unordered_set>

// Defines token types
enum class TokenType {
    DelimiterOpen,
    DelimiterClose,
    Operator,
    Number,
    Function,
    Letter,
    Unknown
};

// Specifies token types
inline std::string_view delimitersOpen      = "([{";
inline std::string_view delimitersClose     = ")]}";
inline std::string_view operators           = "+-/*^!";
inline std::string_view number              = "1234567890.";
inline std::string_view letter              = "abcdefghijklmnopqrstuvwxyz";
inline std::unordered_set<std::string> functions = { // Change evaluateFunction in Evaluator.cpp when updating list
    "sqrt","ln","sin","cos","tan","csc","sec","cot" };

// Check if a given str is a function
inline bool isFunction(const std::string& str) {
    return functions.contains(str);
}

struct Token {
    std::string mValue;
    TokenType mType;

    // Constructor that sets the token type based on what the value is
    Token(const std::string& value) { setValue(value); }

    bool valueInTokenType(std::string_view strView) const { return (strView.find(this->mValue) != std::string_view::npos); }

    void setValue(const std::string& value) {
        this->mValue = value;
        if(valueInTokenType(delimitersOpen)) mType = TokenType::DelimiterOpen;
        else if(valueInTokenType(delimitersClose)) mType = TokenType::DelimiterClose;
        else if(valueInTokenType(operators)) mType = TokenType::Operator;
        else if(valueInTokenType(number)) mType = TokenType::Number;
        else if(valueInTokenType(letter)) mType = TokenType::Letter;
        else mType = TokenType::Unknown;
    }
};