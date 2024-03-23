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

void printHelp() {
    std::cout << "Usage: program_name [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -o <output_file>    Output file\n";
    std::cout << "  -asm                Output as x86_64 ASM\n";
    std::cout << "  -f <input_file>     Choose the file to input\n";
    std::cout << "  -gcc                Choose GCC as the Linker instead of LD\n";
    std::cout << "  -debug              Enable debug mode\n";
    std::cout << "  -show-tokens        Show tokens\n";
}

int main(int argc, char* argv[])
{
    CLI_cmd cli;

    if (argc == 1)
    {
        std::cerr << "No arguments found, please do -help for an argument list\n";
        return 1;
    }
    std::string mode = "";


    bool hasInputFile = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o" && i + 1 < argc) {
            cli.output_file = argv[++i];
        } else if (arg == "-asm") {
            cli.delete_asm = false;
        } else if (arg == "-f" && i + 1 < argc) {
            cli.input_file = argv[++i];
            hasInputFile = true;
        } else if (arg == "-debug") {
            cli.useDebug = true;
        } else if (arg == "-show-tokens") {
            cli.showTokens = true;
        } else if (arg == "-gcc") {
            cli.linker = "gcc";
        } else if (arg == "-help") {
            printHelp();
            return 0;
        } else {
            std::cerr << "Invalid argument: " << arg << ".\n";
            return 1;
        }
    }

    if (cli.input_file == "")
    {
        std::cerr << "No input files\n";
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
        std::cout << pt.type << " * " << pt.val << " * " << pt.params.size() << "\n";
    }
    #endif

    std::string compiled_code = Compiler::compileToAssembly(ptokens);

    // time to output
    Compiler::outputToFile(compiled_code, argv, ptokens, cli);

    auto end = std::chrono::high_resolution_clock::now();
    auto exec_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Compilation time: " << exec_time.count() << "ms\n";

    return 0;
}