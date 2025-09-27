; strlen(3):
; size_t strlen(const char *s);

section .text
    global  _ft_strlen

_ft_strlen:
    xor rax, rax
    jmp loop

loop:
    cmp [rdi + rax], 0
    jz ret
    inc rax
    jmp loop