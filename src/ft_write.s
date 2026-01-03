; write(2):
; ssize_t write(int fd, const void buf[.count], size_t count);

section .text
global  ft_write
extern  __errno_location

ft_write:
	mov rax, 1
	syscall
	test rax, rax
	js _error
	ret

_error:
    neg rax
	push rax
	call __errno_location wrt ..plt
	pop rdx
	mov [rax], rdx
	mov rax, -1
	ret
