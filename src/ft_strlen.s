; strlen(3):
; size_t strlen(const char *s);
; 1st arg (s) = rdi

global  ft_strlen

section .text
ft_strlen:
	xor rax, rax ; clear rax

.loop:
	cmp byte [rdi + rax], 0 ; compare byte at (rdi + rax) with 0
	jz .return ; jump if zero
	inc rax ; increment rax
	jmp .loop ; jump to .loop

.return:
	ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
; .note.GNU-stack: special section name recognized by the GNU linker to configure stack execution policies.
; noalloc: ensures the section is merely informational and not allocated in memory at runtime.
; noexec: explicitly declares that the stack should not be granted execute permissions.
; nowrite: indicates that the metadata section itself should not be writable.
; progbits: specifies that the section contains explicit contents stored in the object file.