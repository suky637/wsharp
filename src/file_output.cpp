#include "file_output.hpp"

std::vector<std::string> Compiler::get_include_files(std::vector<Parsed_Token> tokens)
    {
        std::vector<std::string> buffer{};
        for (auto const& v : tokens)
        {
            if (v.type == P_INCLUDE)
            {
                buffer.push_back(v.val);
            }
        }
        return buffer;
    }

void Compiler::outputToFile(std::string compiled_code, char** argv, std::vector<Parsed_Token> ptokens, CLI_cmd cli)
    {
        std::ofstream outASM("out.asm");
        outASM << compiled_code;
        outASM.close();

        std::string path_rel = argv[0];
        path_rel = path_rel.substr(2, path_rel.size()-2);
    
        std::string path_abs = std::filesystem::absolute(path_rel).string();

        // Checking for other files (mainly ASM then W#)
        std::vector<std::string> include_files = get_include_files(ptokens);
        for (auto const& v : include_files)
        {
            if (v.substr(v.size()-3, 3) == ".ws")
            {
            
            }
            else
            {
                std::string lib = readFile(path_abs.substr(0, path_abs.size()-10) + "lib/" + v);
                std::ofstream outLib(v);
                outLib << lib;
                outLib.close();
            }
        }


        system("nasm -f elf64 -o out.o out.asm");
        std::string gcc_cmd = cli.linker + " -o " + cli.output_file + " out.o";
        system(gcc_cmd.c_str());

        if (cli.delete_asm)
        {
            std::filesystem::remove("out.asm");
        }
        for (auto const& v : include_files)
        {
            if (v.substr(v.size()-3, 3) == ".ws")
            {
            
            }
            else
            {
                std::filesystem::remove(v);
            }
        }

        std::filesystem::remove("out.o");
    }