; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg = rdi, 2nd arg = rsi

section .text
global  _ft_strcpy

_ft_strcpy:
    xor rax, rax
    push rdi;
    jmp loop

loop:
    cmp [rsi], 0
    je exit
    mov rax, [rsi]
    mov [rdi], rax
    inc rdi
    inc rsi
    jmp loop

exit:
    mov [rdi], 0
    pop rax
    ret
