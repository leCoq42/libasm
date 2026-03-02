; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg (dst) = rdi, 2nd arg (src) = rsi

global  ft_strcpy

section .text
ft_strcpy:
    xor rax, rax
    push rdi

.loop:
    mov al, [rsi]
    mov [rdi], al
    test al, al
    jz .return
    inc rdi
    inc rsi
    jmp .loop

.return:
    pop rax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
