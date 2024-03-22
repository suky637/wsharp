global _start

section .text
%include "write_int"
_start:
	mov rax, 0x1
	mov rdi, 1
	mov rsi, str_0
	mov rdx, 61
	syscall

	mov RAX, 7
	mov RDX, 14
	mov RAX, RAX
	add RAX, RDX
	mov rdi, 0
	call writeInt

	mov rax, 0x3C
	mov rdi, 0
	syscall

	ret


section .data
str_0: db "Hello World!", 0xA, "This is printing a number from external lib: ", 0xA
