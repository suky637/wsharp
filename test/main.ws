using "quick_io"
using "write_int"
using "math"

global _start

fn _start
{
    RAX = 10
    RBX = 2
    RDX = 0
    divide { }
    push RDX
    push RAX
    write {1, "RESULT: " }
    pop RAX
    writeInt { }
    write {1, ", Low: "}
    pop RDX
    RAX = RDX
    writeInt { }
    writeEOL { }
    exit { 0 }
}