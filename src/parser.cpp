#include "parser.hpp"

Parsed_TokenType Compiler::lex_to_par_for_args(TokenType type)
    {
        if (type == TokenType::STRING)
            return Parsed_TokenType::P_STRING;
        if (type == TokenType::NUMBER)
            return Parsed_TokenType::P_INT;
        if (type == TokenType::REGISTER)
            return Parsed_TokenType::P_REG;
        return Parsed_TokenType::P_NONE;
    }

std::pair<std::vector<Parsed_Token>, int> Compiler::get_args(int start, std::vector<Token> tokens)
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

std::vector<Parsed_Token> Compiler::parser(std::vector<Token> tokens)
{
    #ifdef DEBUG
    std::cout << "----------- PARSER -------------\n";
    #endif
    std::vector<Parsed_Token> ptokens{};

    Parsed_Token buffer{};
    int i = 0;

    while (i < tokens.size())
    {
        buffer = {};
        if (tokens.at(i).type == TokenType::FUNCTION && tokens.at(i+1).type == TokenType::UNKNOWN && tokens.at(i+2).type == TokenType::START_BLOCK)
        {
            buffer.type = P_FUNCTION;
            if (tokens.at(i+1).val == "_start" || tokens.at(i+1).val == "main")
                buffer.val = tokens.at(i+1).val;
            else
                buffer.val = "func" + tokens.at(i+1).val;
            ptokens.push_back(buffer);

            i += 3;
        }
        else if (tokens.at(i).type == TokenType::END_BLOCK)
        {
            buffer.type = P_EOF;
            ptokens.push_back(buffer);
            i += 1;
        }
        else if (tokens.at(i).type == TokenType::INCLUDE && tokens.at(i+1).type == TokenType::STRING)
        {
            buffer.type = P_INCLUDE;
            buffer.val = tokens.at(i+1).val;
            ptokens.push_back(buffer);
            i += 2;
        }
        else if (tokens.at(i).type == TokenType::GLOBAL && tokens.at(i+1).type == TokenType::UNKNOWN)
        {
            buffer.type = P_GLOBAL;
            buffer.val = tokens.at(i+1).val;
            ptokens.push_back(buffer);
            i += 2;
        }
        else if (tokens.at(i).type == TokenType::UNKNOWN && tokens.at(i+1).type == TokenType::START_BLOCK)
        {
            buffer.type = Parsed_TokenType::P_CALL;
            buffer.val = "func" + tokens.at(i).val;

            // TODO: do it to any functions
            if (tokens.at(i+1).type == TokenType::START_BLOCK && tokens.at(i+2).type == TokenType::END_BLOCK)
            {
                i += 3;
            }
            else if (tokens.at(i+1).type == TokenType::START_BLOCK)
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
        else if (tokens.at(i).type == TokenType::IF_STATEMENT && (tokens.at(i+1).type == TokenType::NUMBER || tokens.at(i+1).type == TokenType::REGISTER) && (tokens.at(i+3).type == TokenType::NUMBER || tokens.at(i+3).type == TokenType::REGISTER))
        {
            buffer.type = P_IF;
            // verify type
            if (tokens.at(i+2).type == TokenType::STA_EQUAL)
            {
                buffer.val = "je";
            }
            else if (tokens.at(i+2).type == TokenType::STA_GREATER)
            {
                buffer.val = "jg";
            }
            else if (tokens.at(i+2).type == TokenType::STA_GREATER_EQ)
            {
                buffer.val = "jge";
            }
            else if (tokens.at(i+2).type == TokenType::STA_LOWER)
            {
                buffer.val = "jl";
            }
            else if (tokens.at(i+2).type == TokenType::STA_LOWER_EQ)
            {
                buffer.val = "jle";
            }
            else if (tokens.at(i+2).type == TokenType::STA_NEQUAL)
            {
                buffer.val = "jne";
            }

            if (tokens.at(i+1).type == NUMBER)
            {
                Parsed_Token pt{};
                pt.type = P_INT;
                pt.val = tokens.at(i+1).val;
                buffer.params.push_back(pt);
            }
            else if (tokens.at(i+1).type == REGISTER)
            {
                Parsed_Token pt{};
                pt.type = P_REG;
                pt.val = tokens.at(i+1).val;
                buffer.params.push_back(pt);
            }

            if (tokens.at(i+3).type == NUMBER)
            {
                Parsed_Token pt{};
                pt.type = P_INT;
                pt.val = tokens.at(i+3).val;
                buffer.params.push_back(pt);
            }
            else if (tokens.at(i+3).type == REGISTER)
            {
                Parsed_Token pt{};
                pt.type = P_REG;
                pt.val = tokens.at(i+3).val;
                buffer.params.push_back(pt);
            }

            i += 4;
            if (tokens.at(i).type == TokenType::START_BLOCK)
            {
                i++;
                Parsed_Token pt{};
                pt.val = tokens.at(i).val;
                pt.type = Parsed_TokenType::P_CALL;
                buffer.params.push_back(pt);
                i+=2;
            }
            ptokens.push_back(buffer);
        }
        else if (tokens.at(i).type == TokenType::REGISTER && tokens.at(i+1).type == TokenType::EQUAL)
        {
            if (tokens.at(i+2).type == TokenType::NUMBER || tokens.at(i+2).type == TokenType::REGISTER)
            {
                buffer.type = P_SET_REG;
                buffer.val = tokens.at(i).val;
                std::string reg = tokens.at(i).val;
                Parsed_Token c_pt{};
                c_pt.type = P_INT;
                c_pt.val = tokens.at(i+2).val;

                buffer.params.push_back(c_pt);
                
                ptokens.push_back(buffer);
                buffer = {};
                
                if (tokens.at(i+3).type == TokenType::OPERATION)
                {
                    // Operations
                    int j = i+3;
                    bool operation = true;
                    while ((operation && tokens.at(j).type == TokenType::OPERATION) || (!operation && (tokens.at(j).type == TokenType::NUMBER || tokens.at(j).type == TokenType::REGISTER)))
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
                            Parsed_Token lc_pt{};
                            if (tokens.at(j).type == NUMBER)
                            {
                                lc_pt.type = P_INT;
                            }
                            else
                            {
                                lc_pt.type = P_REG;
                                
                            }
                            lc_pt.val = tokens.at(j).val;
                            std::cout << lc_pt.val << "\n";
                            buffer.params.push_back(lc_pt);
                            ptokens.push_back(buffer);
                        }
                        operation = !operation;
                        j++;
                    }
                    i = j-3;
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
        else if (tokens.at(i).type == PUSH && tokens.at(i+1).type == REGISTER)
        {
            buffer.type = P_PUSH;
            buffer.val = tokens.at(i+1).val;
            ptokens.push_back(buffer);
            i += 2;
        }
        else if (tokens.at(i).type == POP && tokens.at(i+1).type == REGISTER)
        {
            buffer.type = P_POP;
            buffer.val = tokens.at(i+1).val;
            ptokens.push_back(buffer);
            i += 2;
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