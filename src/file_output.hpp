#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "types.hpp"
#include "global_functions.hpp"

namespace Compiler
{
    std::vector<std::string> get_include_files(std::vector<Parsed_Token> tokens);   

    void outputToFile(std::string compiled_code, char** argv, std::vector<Parsed_Token> ptokens, CLI_cmd cli);
};