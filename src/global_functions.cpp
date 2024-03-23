#include "global_functions.hpp"

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