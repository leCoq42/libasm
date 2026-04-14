; strcmp(3):
; int strcmp(const char *s1, const char *s2);
; 1st arg (s1) = rdi, 2nd arg (s2) = rsi

global  ft_strcmp

section .text
ft_strcmp:
	xor rax, rax ; clear rax
	xor rdx, rdx ; clear rdx

.loop:
	mov al, [rdi] ; load byte from s1 into al
	mov dl, [rsi] ; load byte from s2 into dl
	cmp al, dl ; compare al and dl
	jne .return ; jump if not equal
	test al, al ; check if al is zero
	jz .return ; jump if zero

	inc rdi ; increment s1 pointer
	inc rsi ; increment s2 pointer
	jmp .loop ; jump to .loop

.return:
	sub rax, rdx ; calculate the difference between rax and rdx
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
