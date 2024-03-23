#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "types.hpp"

namespace Compiler
{
    std::vector<Token> lexer(std::string text);
};