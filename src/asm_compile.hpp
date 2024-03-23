#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "types.hpp"
namespace Compiler
{
std::string get_constant(std::string v);

std::string args_tostring(std::vector<Parsed_Token> args, std::map<std::string, std::string>* string_constants);

std::string compileToAssembly(std::vector<Parsed_Token> tokens);
};