#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "types.hpp"

namespace Compiler
{
    Parsed_TokenType lex_to_par_for_args(TokenType type);

    std::pair<std::vector<Parsed_Token>, int> get_args(int start, std::vector<Token> tokens);

    std::vector<Parsed_Token> parser(std::vector<Token> tokens);
};