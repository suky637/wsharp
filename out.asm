%include "quick_io"
%include "write_int"
global _start

section .text
_start:
	mov rax, 0x1
	mov rdi, 1
	mov rsi, str_0
	mov rdx, 13
	syscall

	mov rax, 0x3C
	mov rdi, 0
	syscall

	ret


section .data
str_0: db "Hello, World!"
