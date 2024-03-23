#include "lexer.hpp"

std::vector<Token> Compiler::lexer(std::string text)
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
            if (text.at(i+1) != '=')
            {
            tok.type = TokenType::EQUAL;
            tok.val = "";
            tokens.push_back(tok);
            }
            else
            {
                tok.type = TokenType::STA_EQUAL;
                tok.val = "";
                tokens.push_back(tok);
            }
        }
        else if (c == '>')
        {
            if (text.at(i+1) != '=')
            {
                tok.type = TokenType::STA_GREATER;
                tok.val = "";
                tokens.push_back(tok);
            }
            else
            {
                tok.type = TokenType::STA_GREATER_EQ;
                tok.val = "";
                tokens.push_back(tok);
            }
        }
        else if (c == '<')
        {
            if (text.at(i+1) != '=')
            {
                tok.type = TokenType::STA_LOWER;
                tok.val = "";
                tokens.push_back(tok);
            }
            else
            {
                tok.type = TokenType::STA_LOWER_EQ;
                tok.val = "";
                tokens.push_back(tok);
            }
        }
        else if (c == '!')
        {
            if (text.at(i+1) == '=')
            {
                tok.type = TokenType::STA_NEQUAL;
                tok.val = "";
                tokens.push_back(tok);
            }
            else
            {
                std::cerr << "[LEXING ERROR] character '!' isn't accompagned with an '='.";
                exit(1);
            }
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
            else if (buffer == "using")
            {
                tok.type = TokenType::INCLUDE;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "if")
            {
                tok.type = TokenType::IF_STATEMENT;
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