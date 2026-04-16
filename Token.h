#pragma once

#include <string>

enum class TokenType {
    DelimiterOpen,
    DelimiterClose,
    Operator,
    Number,
    SubExpression,
    Unknown
};

inline std::string_view delimitersOpen  = "([{";
inline std::string_view delimitersClose = ")]}";
inline std::string_view operators       = "+-/*^";
inline std::string_view digits          = "1234567890";

struct Token {
    std::string value;
    TokenType type;

    // Constructor that sets the token type based on what the value is
    Token(const std::string& value = "[SubExpr]") : value{ value } {
        if(delimitersOpen.find(this->value) != std::string_view::npos) type = TokenType::DelimiterOpen;
        else if(delimitersClose.find(this->value) != std::string_view::npos) type = TokenType::DelimiterClose;
        else if(operators.find(this->value) != std::string_view::npos) type = TokenType::Operator;
        else if(digits.find(this->value) != std::string_view::npos) type = TokenType::Number;
        else if(this->value == "[SubExpr]") type = TokenType::SubExpression;
        else type = TokenType::Unknown;
    }
};