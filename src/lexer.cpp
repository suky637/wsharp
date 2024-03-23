#include "lexer.hpp"

std::vector<Token> Compiler::lexer(std::string text)
{
    std::vector<Token> tokens{};
    tokens.reserve(text.size() / 2); // Reserve space for tokens to avoid frequent reallocations
    std::string buffer;
    bool is_doing_string = false;
    
    for (size_t i = 0; i < text.size(); ++i)
    {
        Token tok;
        char c = text.at(i);

        if (is_doing_string)
        {
            while (text.at(i) != '"') {
                buffer += text.at(i);
                ++i;
            }
            is_doing_string = false;
            tok.type = TokenType::STRING;
            tok.val = std::move(buffer);
            tokens.push_back(std::move(tok));
        }
        else if (std::isdigit(c))
        {
            buffer += c;
            while (std::isdigit(text.at(i + 1))) {
                buffer += text.at(++i);
            }
            tok.type = TokenType::NUMBER;
            tok.val = std::move(buffer);
            tokens.push_back(std::move(tok));
            //buffer = "";
        }
        else if (std::isspace(text.at(i)))
        {
            continue;
        }
        
        else if (c == '"')
        {
            is_doing_string = true;
        }
        else if (c == '=')
        {
            tok.val = "";
            if (text.at(i + 1) == '=') {
                ++i;
                tok.type = TokenType::STA_EQUAL;
            } else {
                tok.type = TokenType::EQUAL;
            }
            tokens.push_back(std::move(tok));
        }
        else if (c == '{' || c == '}' || c == ',' || c == '+' || c == '-' || c == '*' || c == '/') {
            // Single character tokens
            tok.val = c;
            switch (c) {
                case '{': tok.type = TokenType::START_BLOCK; break;
                case '}': tok.type = TokenType::END_BLOCK; break;
                case ',': tok.type = TokenType::COMMA_SEP; break;
                case '+': case '-': case '*': case '/':
                    tok.type = TokenType::OPERATION; break;
            }
            tokens.push_back(std::move(tok));
        } 
        else if (c == '>' || c == '<' || c == '!') {
            // Handle '>', '<', '>=', '<=', '!='
            if (i + 1 < text.size() && text[i + 1] == '=') {
                tok.type = (c == '>') ? TokenType::STA_GREATER_EQ :
                           (c == '<') ? TokenType::STA_LOWER_EQ :
                                        TokenType::STA_NEQUAL;
                tok.val = (c == '!') ? "!=" : std::string(1, c) + "=";
                tokens.push_back(tok);
                ++i;
            } else {
                tok.type = (c == '>') ? TokenType::STA_GREATER :
                           (c == '<') ? TokenType::STA_LOWER :
                                        TokenType::UNKNOWN;
                tok.val = std::string(1, c);
                tokens.push_back(tok);
            }
        }
        else
        {
            buffer += c;
            while (std::isalnum(text.at(i + 1))) {
                buffer += text.at(++i);
            }
            
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
            else if (buffer == "RBX")
            {
                tok.type = TokenType::REGISTER;
                tok.val = "RBX";
                tokens.push_back(tok);
            }
            else if (buffer == "return")
            {
                tok.type = TokenType::RETURN;
                tok.val = "R9";
                tokens.push_back(tok);
            }
            else if (buffer == "push")
            {
                tok.type = TokenType::PUSH;
                tok.val = "";
                tokens.push_back(tok);
            }
            else if (buffer == "pop")
            {
                tok.type = TokenType::POP;
                tok.val = "";
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