# W# Compiled Language
this is a W.I.P. Programming language

The goal of this language is to bring low-level to an higher level by keeping the low-level things.

Why should you use this language?

*because it can be use as a gateway between higher level language and assembly.*



# Install Requirement
- A linux machine
- A x86_64 CPU
- NASM
- GCC (Optional)

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

# Important notes

If you are using GCC as linker, the main function will be "main". if you're using the default one, *ld* it is "_start".

# Q&A

- Why is *GCC* Optional?

Because you can use *ld* as the linker (default linker).

- In what language is it compiled to?

The language is compiled to Assembly, that is why it currently only supports x86_64.