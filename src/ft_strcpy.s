; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg (dst) = rdi, 2nd arg (src) = rsi

section .text
global  _ft_strcpy

_ft_strcpy:
    xor rax, rax
    push rdi;
    jmp loop

loop:
    cmp [rsi], 0
    je return
    mov rax, [rsi]
    mov [rdi], rax
    inc rdi
    inc rsi
    jmp loop

return:
    mov [rdi], 0
    pop rax
    ret
