%include "write_int"
%include "quick_io"
global _start

section .text
_start:
	mov rax, 0x1
	mov rdi, 1
	mov rsi, str_0
	mov rdx, 23
	syscall

	call quickInput

	mov rax, 0x1
	mov rdi, 1
	mov rsi, RSI
	mov rdx, 128
	syscall

	mov rax, 0x3C
	mov rdi, 0
	syscall

	ret


section .data
str_0: db "Please write any text: "
