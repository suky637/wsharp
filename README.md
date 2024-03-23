# W# Compiled Language
this is a W.I.P. Programming language

The goal of this language is to bring low-level to an higher level by keeping the low-level things.

Why should you use this language?
*because it can be use as a gateway between higher level language and assembly*

# Install Requirement
- A linux machine
- A x86_64 CPU
- NASM
- GCC (Optionnal)

# Example code
```
using "write_int"

global _start

fn _start
{
    write { 1, "Hello World!\nThis is printing a number from external lib: \n"}
    
    RAX = 7
    RDX = 14
    RAX = RAX + RDX
    writeInt { 0 }
    exit { 0 }
}
```
Compiling:
```
wsharp -o main -f main.ws
./main
```
Which outputs to:
```
Hello World!
This is printing a number from external lib: 
21
```

# Getting Started

**TODO**