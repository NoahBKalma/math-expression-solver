#pragma once

#include <memory>

#include "Tokens.h"

struct Node {
    Token token;
    std::unique_ptr<Node> leftNode;
    std::unique_ptr<Node> rightNode;

    Node(const Token& token) :
        token{token},
        leftNode{ nullptr },
        rightNode{ nullptr} {}
};