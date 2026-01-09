; read(2):
; ssize_t read(int fd, void *buf, size_t count);

extern  __errno_location

global  ft_read

section .text
ft_read:
	mov rax, 0
	syscall
	test rax, rax
	js .error
	ret

.error:
	neg rax
	push rax
	call __errno_location wrt ..plt
	pop rdx
	mov [rax], edx
	mov rax, -1
	ret
