using "write_int"
using "quick_io"

global _start

fn _start
{
    write { 1, "Please write any text: " }
    quickInput {}
    write {1, RSI}

    exit { 0 }
}