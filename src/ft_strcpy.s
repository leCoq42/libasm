; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg (dst) = rdi, 2nd arg (src) = rsi

global  ft_strcpy

section .text
ft_strcpy:
	mov rax, rdi ; copy dst pointer to rax for return value

.loop:
	mov dl, [rsi] ; load byte from src into dl
	mov [rdi], dl ; store byte from dl into dst
	test dl, dl ; performs a bitwise logical AND operation between two operands
	jz .return ; jump if zero
	inc rdi ; increment dst pointer
	inc rsi ; increment src pointer
	jmp .loop ; jump to .loop

.return:
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
