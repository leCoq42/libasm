; strdup(3):
; char *strdup(const char *s);
; 1st arg (s) = rdi

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
	jz .malloc_fail

	mov rsi, rbx
	mov rdi, rax
	call ft_strcpy

	pop rbx
	ret

.malloc_fail:
	xor rax, rax
	pop rbx
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
