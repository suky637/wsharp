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