; strlen(3):
; size_t strlen(const char *s);
; 1st arg (s) = rdi

global  ft_strlen

section .text
ft_strlen:
    xor rax, rax

.loop:
    cmp byte [rdi + rax], 0
    jz .return
    inc rax
    jmp .loop

.return:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
