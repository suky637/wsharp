#pragma once
#include <string>
#include <vector>

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
    INCLUDE,
    IF_STATEMENT,
    STA_EQUAL,
    STA_GREATER,
    STA_LOWER,
    STA_GREATER_EQ,
    STA_LOWER_EQ,
    STA_NEQUAL,
    PUSH,
    POP
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
    P_INCLUDE,
    P_IF,
    P_REG,
    P_PUSH,
    P_POP
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
    std::string mode = "";
    std::string output_file = "a";
    std::string input_file = "";
    bool delete_asm = true;
    std::string linker = "ld";
};