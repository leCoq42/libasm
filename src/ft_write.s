; write(2):
; ssize_t write(int fd, const void *buf, size_t count);
; 1st arg (fd) = rdi, 2nd arg (buf) = rsi, 3rd arg (count) = rdx

extern  __errno_location

global  ft_write

section .text
ft_write:
	mov rax, 1
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
