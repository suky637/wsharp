cmake_minimum_required(VERSION 3.20)

project(WSharp)

set(CMAKE_CXX_STANDARD_REQUIRED, 20)

add_executable(wsharp src/main.cpp src/asm_compile.cpp src/file_output.cpp src/global_functions.cpp src/lexer.cpp src/parser.cpp)