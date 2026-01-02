; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg (dst) = rdi, 2nd arg (src) = rsi

section .text
global  ft_strcpy

ft_strcpy:
    xor rax, rax
    push rdi

loop:
    cmp byte [rsi], 0
    je return
    mov al, [rsi]
    mov [rdi], al
    inc rdi
    inc rsi
    jmp loop

return:
    mov byte [rdi], 0
    pop rax
    ret
