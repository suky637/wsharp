%include "quick_io"
%include "write_int"
%include "math"
global _start

section .text
_start:
	mov RAX, 3
	mov RBX, 2
	mov RDX, 0
	call funcdivide

	push RDX
	push RAX
	mov rax, 0x1
	mov rdi, 1
	mov rsi, str_0
	mov rdx, 8
	syscall

	pop RAX
	call funcwriteInt

	mov rax, 0x1
	mov rdi, 1
	mov rsi, str_1
	mov rdx, 7
	syscall

	pop RDX
	mov RAX, RDX
	call funcwriteInt

	call funcwriteEOL

	mov rax, 0x3C
	mov rdi, 0
	syscall

	ret


section .data
str_1: db ", Low: "
str_0: db "RESULT: "
