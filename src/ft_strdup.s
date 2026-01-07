; strdup(3):
; char *strdup(const char *s);


section .text
global  ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy


ft_strdup:
	push rbx
	mov rbx, rdi
	call ft_strlen

	inc rax
	mov rdi, rax
	call malloc
	
	cmp rax, 0
	je .malloc_fail

	mov rsi, rbx
	mov rdi, rax
	call ft_strcpy

	pop rbx
	ret

.malloc_fail:
	xor rax, rax
	pop rbx
	ret
