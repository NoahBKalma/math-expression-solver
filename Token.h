#pragma once

#include <string>

enum class TokenType {
    DelimiterOpen,
    DelimiterClose,
    Operator,
    Number,
    Unknown
};

inline std::string_view delimitersOpen  = "([{";
inline std::string_view delimitersClose = ")]}";
inline std::string_view operators       = "+-/*^";
inline std::string_view digits          = "1234567890";

struct Token {
    std::string value;
    TokenType type;

    Token(const std::string& value) : value{ value } {
        if(delimitersOpen.find(value) != std::string_view::npos) type = TokenType::DelimiterOpen;
        else if(delimitersClose.find(value) != std::string_view::npos) type = TokenType::DelimiterClose;
        else if(operators.find(value) != std::string_view::npos) type = TokenType::Operator;
        else if(digits.find(value) != std::string_view::npos) type = TokenType::Number;
        else type = TokenType::Unknown;
    }
};