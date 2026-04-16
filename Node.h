#pragma once

#include <memory>
#include <vector>

#include "Token.h"

struct Node {
    std::vector<Token> tokens;
    std::vector<std::unique_ptr<Node>> children;

    Node(const std::vector<Token>& tokens) :
        tokens{tokens} {}
};