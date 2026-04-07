; strlen(3):
; size_t strlen(const char *s);
; 1st arg (s) = rdi

global  ft_strlen

section .text
ft_strlen:
	xor rax, rax ; clear rax

.loop:
	cmp byte [rdi + rax], 0 ; compare byte at (rdi + rax) with 0
	jz .return ; jump if zero
	inc rax ; increment rax
	jmp .loop ; jump to .loop

.return:
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
