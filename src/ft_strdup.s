; strdup(3):
; char *strdup(const char *s);
; 1st arg (s) = rdi

extern malloc
extern ft_strlen
extern ft_strcpy

global  ft_strdup

section .text
ft_strdup:
	push rbx ; save rbx on stack
	mov rbx, rdi ; copy the input string pointer to rbx for later use
	call ft_strlen

	inc rax
	mov rdi, rax ; set rdi to the length of the string + 1 for null terminator
	call malloc wrt ..plt ; call malloc to allocate memory for the new string. 
	; wrt ..plt (With Respect To the Procedure Linkage Table): forces the linker to resolve the function's memory address dynamically at runtime, rather than attempting to hardcode a fixed absolute address.
	
	test rax, rax ; check if malloc returned NULL
	jz .malloc_fail ; jump to malloc_fail if malloc failed

	mov rsi, rbx ; set rsi to the original string pointer
	mov rdi, rax ; set rdi to the newly allocated memory pointer
	call ft_strcpy ; call ft_strcpy to copy the string from rbx to rax

	pop rbx ; restore rbx from stack
	ret

.malloc_fail:
	xor rax, rax ; set rax to 0 to indicate failure
	pop rbx ; restore rbx from stack
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
