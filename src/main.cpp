#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <filesystem>

//#define DEBUG_TOKEN

enum TokenType
{
    NONE,
    EXIT,
    RETURN,
    NUMBER,
    FUNCTION,
    START_BLOCK,
    END_BLOCK,
    UNKNOWN,
    COMMA_SEP,
    STRING,
    GLOBAL,
    WRITE,
    REGISTER,
    EQUAL,
    OPERATION,
    INCLUDE
};

struct Token
{
    Token() : type{TokenType::NONE}, val{""}
    {

    }
    TokenType type;
    std::string val;
};

enum Parsed_TokenType
{
    P_NONE,
    P_FUNCTION,
    P_INT,
    P_STRING,
    P_CALL,
    P_RETURN,
    P_EXIT,
    P_SYSCALL,
    P_GLOBAL,
    P_EOF,
    P_SET_REG,
    P_ADD,
    P_SUB,
    P_MUL,
    P_DIV,
    P_INCLUDE
};

struct Parsed_Token
{
    Parsed_Token() : type{Parsed_TokenType::P_NONE}, val{""}
    {

    }
    Parsed_TokenType type;
    std::string val;
    std::vector<Parsed_Token> params;
};

struct CLI_cmd
{
    bool useDebug;
    bool showTokens;
};

void debug_tokens(std::vector<Token> tokens)
{
    for (auto& t : tokens)
    {
        std::cout << t.type << std::endl;
    }
}

std::string readFile(std::string input_file)
{
    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(input_file, std::ios::in);
        contents_stream << input.rdbuf();
        input.close();
        contents = contents_stream.str();
    }
    return contents;
}

std::vector<Token> lexer(std::string text)
{
    std::vector<Token> tokens{};
    std::string buffer = "";
    std::string string_buffer = "";
    bool is_doing_string = false;
    
    for (int i = 0; i < text.size(); i++)
    {
        Token tok;
        char c = text.at(i);

        if (is_doing_string)
        {
            while (text.at(i) != '"')
            {
                string_buffer += text.at(i);
                i++;
                continue;
            }
            #ifdef DEBUG
            std::cout << "String\n";
            #endif
            is_doing_string = false;
            tok.type = TokenType::STRING;
            tok.val = string_buffer;
            tokens.push_back(tok);
            string_buffer = "";
            //buffer = "";
        }
        else if (std::isdigit(c))
        {
            while (std::isdigit(text.at(i)))
            {
                buffer += text.at(i);
                i++;
            }
            i--;

            #ifdef DEBUG
            std::cout << "Number\n";
            #endif
            tok.type = TokenType::NUMBER;
            tok.val = buffer;
            tokens.push_back(tok);
            //buffer = "";
        }
        else if (std::isspace(text.at(i)))
        {
            continue;
        }
        else if (c == '{')
        {
            #ifdef DEBUG
            std::cout << "Open block\n";
            #endif
            tok.type = TokenType::START_BLOCK;
            tok.val = "";
            tokens.push_back(tok);
        }
        else if (c == '}')
        {

            #ifdef DEBUG
            std::cout << "Close Block\n";
            #endif
            tok.type = TokenType::END_BLOCK;
            tok.val = "";
            tokens.push_back(tok);
        }
        else if (c == ',')
        {
            #ifdef DEBUG
            std::cout << "Comma\n";
            #endif
            tok.type = TokenType::COMMA_SEP;
            tok.val = "";
            tokens.push_back(tok);
        }
        else if (c == '"')
        {
            is_doing_string = true;
        }
        else if (c == '=')
        {
            tok.type = TokenType::EQUAL;
            tok.val = "";
            tokens.push_back(tok);
        }
        else if (c == '+')
        {
            tok.type = TokenType::OPERATION;
            tok.val = "+";
            tokens.push_back(tok);
        }
        else if (c == '-')
        {
            tok.type = TokenType::OPERATION;
            tok.val = "-";
            tokens.push_back(tok);
        }
        else if (c == '*')
        {
            tok.type = TokenType::OPERATION;
            tok.val = "*";
            tokens.push_back(tok);
        }
        else if (c == '/')
        {
            tok.type = TokenType::OPERATION;
            tok.val = "/";
            tokens.push_back(tok);
        }
        else
        {
            buffer.push_back(text.at(i));
            i++;
            while (std::isalnum(text.at(i)))
            {
                buffer.push_back(text.at(i));
                i++;
            }
            i--;

            
            if (buffer == "exit")
            {
                #ifdef DEBUG
                std::cout << "Exit\n";
                #endif
                tok.type = TokenType::EXIT;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "fn")
            {
                #ifdef DEBUG
                std::cout << "Function\n";
                #endif
                tok.type = TokenType::FUNCTION;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "global")
            {
                #ifdef DEBUG
                std::cout << "Global\n";
                #endif
                tok.type = TokenType::GLOBAL;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "write")
            {
                #ifdef DEBUG
                std::cout << "Write\n";
                #endif
                tok.type = TokenType::WRITE;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "RAX")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "RAX";
                tokens.push_back(tok);
            }
            else if (buffer == "RDI")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "RDI";
                tokens.push_back(tok);
            }
            else if (buffer == "RSI")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "RSI";
                tokens.push_back(tok);
            }
            else if (buffer == "RDX")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "RDX";
                tokens.push_back(tok);
            }
            else if (buffer == "R10")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "R10";
                tokens.push_back(tok);
            }
            else if (buffer == "R8")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "R8";
                tokens.push_back(tok);
            }
            else if (buffer == "R9")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "R9";
                tokens.push_back(tok);
            }
            else if (buffer == "return")
            {
                tok.type = TokenType::RETURN;
                tok.val = "R9";
                tokens.push_back(tok);
            }
            else if (buffer == "import")
            {
                tok.type = TokenType::INCLUDE;
                tok.val = "";
                tokens.push_back(tok);
            }
            else
            {
                #ifdef DEBUG
                std::cout << "Unknown\n";
                #endif
                tok.type = TokenType::UNKNOWN;
                tok.val = buffer;
                tokens.push_back(tok);
            }

            
        }
        buffer = "";
        
    }

    return tokens;
}

Token advance(std::vector<Token>& tokens, int* index)
{
    Token cur{};
    *index = 1;
    if (*index < tokens.size())
        cur = tokens[*index];
    return cur;
}

Parsed_TokenType lex_to_par_for_args(TokenType type)
{
    if (type == TokenType::STRING)
        return Parsed_TokenType::P_STRING;
    if (type == TokenType::NUMBER)
        return Parsed_TokenType::P_INT;
    return Parsed_TokenType::P_NONE;
}

std::pair<std::vector<Parsed_Token>, int> get_args(int start, std::vector<Token> tokens)
{
    std::vector<Parsed_Token> buffer{};
    int i = 0;
    for (int j = start; j < tokens.size(); j++)
    {
        if (tokens.at(j).type == TokenType::END_BLOCK || tokens.at(j).type == TokenType::NONE)
        {
            break;
        }
        if (tokens.at(j).type == TokenType::COMMA_SEP || tokens.at(j).type == TokenType::START_BLOCK)
        {
            continue;
        }
        Parsed_Token pbuf{};
        pbuf.type = lex_to_par_for_args(tokens.at(j).type);
        pbuf.val = tokens.at(j).val;
        buffer.push_back(pbuf);
        i = j+1;
    }
    
    return std::pair<std::vector<Parsed_Token>, int>(buffer, i);
}

std::vector<Parsed_Token> parser(std::vector<Token> tokens)
{
    #ifdef DEBUG
    std::cout << "----------- PARSER -------------\n";
    #endif
    std::vector<Parsed_Token> ptokens{};

    Parsed_Token buffer{};
    int i = 0;

    #ifdef DEBUG_TOKEN
    int k = 0;
    for (Token tok : tokens)
    {
        std::cout << k << " * " << tok.type << " * " << tok.val << "\n";
        k++;
    }
    #endif

    while (i < tokens.size())
    {
        if (tokens.at(i).type == TokenType::FUNCTION && tokens.at(i+1).type == TokenType::UNKNOWN && tokens.at(i+2).type == TokenType::START_BLOCK)
        {
            buffer.type = P_FUNCTION;
            buffer.val = tokens.at(i+1).val;
            buffer.params = {};
            ptokens.push_back(buffer);

            i += 3;
        }
        else if (tokens.at(i).type == TokenType::END_BLOCK)
        {
            buffer.type = P_EOF;
            buffer.val = "";
            buffer.params = {};
            ptokens.push_back(buffer);
            i += 1;
        }
        else if (tokens.at(i).type == TokenType::INCLUDE && tokens.at(i+1).type == TokenType::STRING)
        {
            buffer.type = P_INCLUDE;
            buffer.val = tokens.at(i+1).val;
            buffer.params = {};
            ptokens.push_back(buffer);
            i += 2;
        }
        else if (tokens.at(i).type == TokenType::GLOBAL && tokens.at(i+1).type == TokenType::UNKNOWN)
        {
            buffer.type = P_GLOBAL;
            buffer.val = tokens.at(i+1).val;
            buffer.params = {};
            ptokens.push_back(buffer);
            i += 2;
        }
        else if (tokens.at(i).type == TokenType::UNKNOWN && tokens.at(i+1).type == TokenType::START_BLOCK)
        {
            buffer.type = Parsed_TokenType::P_CALL;
            buffer.val = tokens.at(i).val;

            // TODO: do it to any functions
            if (tokens.at(i+1).type == TokenType::START_BLOCK)
            {
                int j = i+2;
                std::pair<std::vector<Parsed_Token>, int> args = get_args(j, tokens);
                buffer.params = args.first;
                j = args.second;
                i = j+1;
            }
            else
            {
                std::cerr << "[PARSING ERROR] token " + std::to_string(i+1) + " isn't a '{'.\n";
                exit(1);
            }
            ptokens.push_back(buffer);
        }
        else if (tokens.at(i).type == TokenType::REGISTER && tokens.at(i+1).type == TokenType::EQUAL)
        {
            if (tokens.at(i+2).type == TokenType::NUMBER)
            {
                buffer.type = P_SET_REG;
                buffer.val = tokens.at(i).val;
                std::string reg = tokens.at(i).val;
                Parsed_Token c_pt{};
                c_pt.type = P_INT;
                c_pt.val = tokens.at(i+2).val;
                buffer.params = {};



                buffer.params.push_back(c_pt);
                ptokens.push_back(buffer);
                
                if (tokens.at(i+3).type == TokenType::OPERATION)
                {
                    // Operations
                    int j = i+3;
                    bool operation = true;
                    while ((operation && tokens.at(j).type == TokenType::OPERATION) || (!operation && tokens.at(j).type == TokenType::NUMBER))
                    {

                        if (operation)
                        {
                            if (tokens.at(j).val == "+")
                            {
                                buffer.type = P_ADD;
                                buffer.val = reg;
                            }
                            else if (tokens.at(j).val == "-")
                            {
                                buffer.type = P_SUB;
                                buffer.val = reg;
                            }
                            else if (tokens.at(j).val == "/")
                            {
                                buffer.type = P_DIV;
                                buffer.val = reg;
                            }
                            else if (tokens.at(j).val == "*")
                            {
                                buffer.type = P_MUL;
                                buffer.val = reg;
                            }
                        }
                        else
                        {
                            buffer.params.clear();
                            Parsed_Token lc_pt{};
                            lc_pt.type = P_INT;
                            lc_pt.val = tokens.at(j).val;
                            buffer.params.push_back(lc_pt);
                            ptokens.push_back(buffer);
                        }
                        operation = !operation;
                        j++;
                        i++;
                    }
                }
                i += 3;
            }
        }
        else if (tokens.at(i).type == TokenType::EXIT)
        {
            buffer.type = Parsed_TokenType::P_SYSCALL;
            buffer.val = "exit";

            // TODO: do it to any functions
            if (tokens.at(i+1).type == TokenType::START_BLOCK)
            {
                int j = i+2;
                std::pair<std::vector<Parsed_Token>, int> args = get_args(j, tokens);
                buffer.params = args.first;
                j = args.second;
                i = j+1;
            }
            else
            {
                std::cerr << "[PARSING ERROR] token " + std::to_string(i+1) + " isn't a '{'.\n";
                exit(1);
            }
            ptokens.push_back(buffer);
            
        }
        else if (tokens.at(i).type == TokenType::WRITE)
        {
            buffer.type = Parsed_TokenType::P_SYSCALL;
            buffer.val = "write";

            // TODO: do it to any functions
            if (tokens.at(i+1).type == TokenType::START_BLOCK)
            {
                int j = i+2;
                std::pair<std::vector<Parsed_Token>, int> args = get_args(j, tokens);
                buffer.params = args.first;
                j = args.second;
                i = j+1;
            }
            else
            {
                std::cerr << "[PARSING ERROR] token " + std::to_string(i+1) + " isn't a '{'.\n";
                exit(1);
            }

            ptokens.push_back(buffer);
            
        }
        else
        {
            std::cerr << "[PARSING ERROR] token " << std::to_string(i) << " didn't match\nType: " << std::to_string(tokens.at(i).type) << std::endl;
            std::cerr << "Value: " << tokens.at(i).val << std::endl;
            exit(1);
        }
    }

    return ptokens;
}

std::string get_constant(std::string v)
{
    std::string c = "";
    bool needToAddNewStr = false;
    for (int i = 0; i < v.size(); i++)
    {
        if (v.at(i) == '\\')
        {
            i++;
            if (v.at(i) == '\\')
            {
                c += '\\';
            }
            else if (v.at(i) == 'n')
            {
                c += "\", 0xA";
                needToAddNewStr = true;
            }
            
        }
        else
        {
            if (needToAddNewStr)
            {
                c += ", \"";
                needToAddNewStr = false;
            }
            c += v.at(i);
        }
    }
    if (!needToAddNewStr)
        c += "\"";
    return c;
}

std::string args_tostring(std::vector<Parsed_Token> args, std::map<std::string, std::string>* string_constants)
{
    std::string arguments = "";
    
    for (int i = 0; i < args.size(); i++)
    {
        if (args.at(i).type == P_STRING)
        {
            string_constants->insert(std::pair<std::string, std::string>(args.at(i).val, "str_" + std::to_string(string_constants->size())));
            
            try
            {
                if (i == 0)
                    arguments += "\tmov rdi, " + string_constants->at(args.at(i).val) + "\n";
                else if (i == 1)
                    arguments += "\tmov rsi, " + string_constants->at(args.at(i).val) + "\n";
                else if (i == 2)
                    arguments += "\tmov rdx, " + string_constants->at(args.at(i).val) + "\n";
                else if (i == 3)
                    arguments += "\tmov r10, " + string_constants->at(args.at(i).val) + "\n";
                else if (i == 4)
                    arguments += "\tmov r8, " + string_constants->at(args.at(i).val) + "\n";
                else if (i == 5)
                    arguments += "\tmov r9, " + string_constants->at(args.at(i).val) + "\n";
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            
        }
        else if (args.at(i).type == P_INT)
        {
            if (i == 0)
                arguments += "\tmov rdi, " + args.at(i).val + "\n";
            else if (i == 1)
                arguments += "\tmov rsi, " + args.at(i).val + "\n";
            else if (i == 2)
                arguments += "\tmov rdx, " + args.at(i).val + "\n";
            else if (i == 3)
                arguments += "\tmov r10, " + args.at(i).val + "\n";
            else if (i == 4)
                arguments += "\tmov r8, " + args.at(i).val + "\n";
            else if (i == 5)
                arguments += "\tmov r9, " + args.at(i).val + "\n";
        }
    }
    return arguments;
}

std::string compileToAssembly(std::vector<Parsed_Token> tokens)
{
    std::map<std::string, std::string> string_constants{};
    std::string header = "";
    std::string body = "\nsection .text\n";
    std::string constants = "\nsection .data\n";
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens.at(i).type == P_GLOBAL)
        {
            header += "global " + tokens.at(i).val + "\n";
        }
        else if (tokens.at(i).type == P_FUNCTION)
        {
            body += tokens.at(i).val + ":\n";
        }
        else if (tokens.at(i).type == P_SYSCALL)
        {
            if (tokens.at(i).val == "write")
            {
                body += "\tmov rax, 0x1\n";

                body += args_tostring(tokens.at(i).params, &string_constants);

                body += "\tmov rdx, " + std::to_string(tokens.at(i).params.at(1).val.size()) + "\n\tsyscall\n\n";
            }
            else if (tokens.at(i).val == "exit")
            {
                body += "\tmov rax, 0x3C\n";
                body += args_tostring(tokens.at(i).params, &string_constants);
                body += "\tsyscall\n\n";
            }
        }
        else if (tokens.at(i).type == P_SET_REG)
        {
            body += "\tmov " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
        }
        else if (tokens.at(i).type == P_ADD)
        {
            body += "\tadd " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
        }
        else if (tokens.at(i).type == P_SUB)
        {
            body += "\tsub " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
        }
        else if (tokens.at(i).type == P_EOF)
        {
            body += "\tret\n\n";
        }
        else if (tokens.at(i).type == P_CALL)
        {
            body += args_tostring(tokens.at(i).params, &string_constants);
            body += "\tcall " + tokens.at(i).val + "\n\n";
        }
        else if (tokens.at(i).type == P_INCLUDE)
        {
            body += "%include \"" + tokens.at(i).val + "\"\n";
        }
    }

    for (const auto& [k, v] : string_constants)
    {
        constants += v + ": db \"" + get_constant(k) + "\n";
    }

    return header + body + constants;
}


std::vector<std::string> get_include_files(std::vector<Parsed_Token> tokens)
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

int main(int argc, char* argv[])
{
    CLI_cmd cli;

    if (argc == 1)
    {
        std::cerr << "No arguments found, please do -help for an argument list" << std::endl;
        return 1;
    }
    std::string mode = "";
    std::string output_file = "a";
    std::string input_file = "";
    bool delete_asm = true;
    std::string linker = "ld";

    // CLI INTERFACE
    for (int i = 0; i < argc; i++)
    {
        if (i == 0) continue;
        std::string arg = argv[i];
        if (mode == "-o")
        {
            output_file = arg;
            mode = "";
            continue;
        }
        if (mode == "-f")
        {
            input_file = arg;
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
            delete_asm = false;
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
            linker = "gcc";
        }
        else
        {
            std::cerr << "Invalid argument : " << arg << ".\n";
            exit(1);
        }


    }

    if (input_file == "")
    {
        std::cerr << "No input files" << std::endl;
        return 1;
    }

    // OPENING FILE
    std::string text = readFile(input_file);
    
    // Lexing
    std::vector<Token> tokens = lexer(text);

    // Parsing
    std::vector<Parsed_Token> ptokens = parser(tokens);

    #ifdef DEBUG_TOKEN
    std::cout << "PARSED TOKENS:\n";
    for (Parsed_Token pt : ptokens)
    {
        std::cout << pt.type << " * " << pt.val << " * " << pt.params.size() << std::endl;
    }
    #endif

    std::string compiled_code = compileToAssembly(ptokens);

    // time to output
    std::ofstream outASM("out.asm");
    outASM << compiled_code;
    outASM.close();

    std::string path_rel = argv[0];
    path_rel = path_rel.substr(2, path_rel.size()-2);
    
    std::string path_abs = std::filesystem::absolute(path_rel).string();
    std::cout << path_abs << std::endl;

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
    std::string gcc_cmd = linker + " -o " + output_file + " out.o";
    system(gcc_cmd.c_str());

    if (delete_asm)
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

    return 0;
}