#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <filesystem>
#include <chrono>
#include "types.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "asm_compile.hpp"
#include "global_functions.hpp"
#include "file_output.hpp"

int main(int argc, char* argv[])
{
    CLI_cmd cli;

    if (argc == 1)
    {
        std::cerr << "No arguments found, please do -help for an argument list" << std::endl;
        return 1;
    }
    std::string mode = "";

    // CLI INTERFACE
    for (int i = 0; i < argc; i++)
    {
        if (i == 0) continue;
        std::string arg = argv[i];
        if (mode == "-o")
        {
            cli.output_file = arg;
            mode = "";
            continue;
        }
        if (mode == "-f")
        {
            cli.input_file = arg;
            mode = "";
            continue;
        }

        if (arg == "-help")
        {
            std::cout << "W# ARGUMENTS\n";
            std::cout << "* -o   | output file\n";
            std::cout << "* -asm | output as x86_64 ASM\n";
            std::cout << "* -f   | choose the file to input \n";
            std::cout << "* -gcc | choose GCC as the Linker instead of LD\n";
            return 0;
        }
        else if (arg == "-o")
        {
            mode = "-o";
            continue;
        }
        else if (arg == "-asm")
        {
            cli.delete_asm = false;
            continue;
        }
        else if (arg == "-f")
        {
            mode = "-f";
            continue;
        }
        else if (arg == "-debug")
        {
            cli.useDebug = true;
            continue;
        }
        else if (arg == "-show-tokens")
        {
            cli.showTokens = true;
            continue;
        }
        else if (arg == "-gcc")
        {
            cli.linker = "gcc";
        }
        else
        {
            std::cerr << "Invalid argument : " << arg << ".\n";
            exit(1);
        }


    }

    if (cli.input_file == "")
    {
        std::cerr << "No input files" << std::endl;
        return 1;
    }
    auto start = std::chrono::high_resolution_clock::now();

    // OPENING FILE
    std::string text = readFile(cli.input_file);
    
    // Lexing
    std::vector<Token> tokens = Compiler::lexer(text);

    // Parsing
    std::vector<Parsed_Token> ptokens = Compiler::parser(tokens);

    #ifdef DEBUG_TOKEN
    std::cout << "PARSED TOKENS:\n";
    for (Parsed_Token pt : ptokens)
    {
        std::cout << pt.type << " * " << pt.val << " * " << pt.params.size() << std::endl;
    }
    #endif

    std::string compiled_code = Compiler::compileToAssembly(ptokens);

    // time to output
    Compiler::outputToFile(compiled_code, argv, ptokens, cli);

    auto end = std::chrono::high_resolution_clock::now();
    auto exec_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Compilation time : " << exec_time.count() << "ms\n";

    return 0;
}