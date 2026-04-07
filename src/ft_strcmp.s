; strcmp(3):
; int strcmp(const char *s1, const char *s2);
; 1st arg (s1) = rdi, 2nd arg (s2) = rsi

global  ft_strcmp

section .text
ft_strcmp:
	xor rax, rax ; clear rax
	xor rdx, rdx ; clear rdx
	xor rcx, rcx ; clear rcx

.loop:
	mov al, [rdi + rcx] ; load byte from s1 into al
	mov dl, [rsi + rcx] ; load byte from s2 into dl
	cmp rax, rdx ; compare rax and rdx
	jne .return ; jump if not equal
	test al, al ; check if al is zero
	jz .return ; jump if zero
	inc rcx ; increment index
	jmp .loop ; jump to .loop

.return:
	sub rax, rdx ; calculate the difference between rax and rdx
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
