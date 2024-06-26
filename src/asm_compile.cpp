#include "asm_compile.hpp"

std::string Compiler::get_constant(std::string v)
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

std::string Compiler::args_tostring(std::vector<Parsed_Token> args, std::map<std::string, std::string>* string_constants)
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
        else if (args.at(i).type == P_REG)
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

std::string Compiler::compileToAssembly(std::vector<Parsed_Token> tokens)
{
    std::map<std::string, std::string> string_constants{};
    std::string header = "";
    std::string body = "\nsection .text\n";
    std::string constants = "\nsection .data\n";
    for (int i = 0; i < tokens.size(); i++)
    {
        const Parsed_TokenType& tok_type = tokens.at(i).type;
        switch (tok_type)
        {
        case P_FUNCTION:
            body += tokens.at(i).val + ":\n";
            break;
        case P_GLOBAL:
            header += "global " + tokens.at(i).val + "\n";
            break;
        case P_SYSCALL:
            if (tokens.at(i).val == "write")
            {
                body += "\tmov rax, 0x1\n";

                body += args_tostring(tokens.at(i).params, &string_constants);
                if (tokens.at(i).params.at(1).type != P_REG)
                    body += "\tmov rdx, " + std::to_string(tokens.at(i).params.at(1).val.size()) + "\n\tsyscall\n\n";
                else
                    body += "\tmov rdx, " + std::to_string(128) + "\n\tsyscall\n\n";
            }
            else if (tokens.at(i).val == "exit")
            {
                body += "\tmov rax, 0x3C\n";
                body += args_tostring(tokens.at(i).params, &string_constants);
                body += "\tsyscall\n\n";
            }
            break;
        case P_SET_REG:
            body += "\tmov " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
            break;
        case P_ADD:
            body += "\tadd " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
            break;
        case P_SUB:
            body += "\tsub " + tokens.at(i).val + ", " + tokens.at(i).params.at(0).val + "\n";
            break;
        case P_EOF:
            body += "\tret\n\n";
            break;
        case P_CALL:
            body += args_tostring(tokens.at(i).params, &string_constants);
            body += "\tcall " + tokens.at(i).val + "\n\n";
            break;
        case P_INCLUDE:
            header += "%include \"" + tokens.at(i).val + "\"\n";
            break;
        case P_IF:
            body += "\tcmp " + tokens.at(i).params.at(0).val + ", " + tokens.at(i).params.at(1).val + "\n";
            body += "\t" + tokens.at(i).val + " func" + tokens.at(i).params.at(2).val + "\n";
            break;
        case P_PUSH:
            body += "\tpush " + tokens.at(i).val + "\n";
            break;
        case P_POP:
            body += "\tpop " + tokens.at(i).val + "\n";
            break;
        default:
            break;
        }
    }

    for (const auto& [k, v] : string_constants)
    {
        constants += v + ": db \"" + get_constant(k) + "\n";
    }

    return header + body + constants;
}
