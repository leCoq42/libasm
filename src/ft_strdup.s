; strdup(3):
; char *strdup(const char *s);

extern malloc
extern ft_strlen
extern ft_strcpy

global  ft_strdup

section .text
ft_strdup:
	push rbx
	mov rbx, rdi
	call ft_strlen

	inc rax
	mov rdi, rax
	call malloc wrt ..plt
	
	test rax, rax
	js .malloc_fail

	mov rsi, rbx
	mov rdi, rax
	call ft_strcpy

	pop rbx
	ret

.malloc_fail:
	xor rax, rax
	pop rbx
	ret
