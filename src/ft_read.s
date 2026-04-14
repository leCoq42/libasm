; read(2):
; ssize_t read(int fd, void *buf, size_t count);
; 1st arg (fd) = rdi, 2nd arg (buf) = rsi, 3rd arg (count) = rdx

extern  __errno_location

global  ft_read

section .text
ft_read:
	mov rax, 0 ; 0 is the syscall number for read
	syscall ; invoke the system call
	cmp rax, 0 ; check if rax is negative
	jl .error ; jump to error handling if negative
	ret ; return from function

.error:
	neg rax ; negate rax to get the positive error code
	push rax ; save error code on stack
	call __errno_location wrt ..plt ; call __errno_location to get pointer to errno
	pop rdi ; restore error code into rdi
	mov [rax], edi ; store error code in errno
	mov rax, -1 ; return -1 to indicate error
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
