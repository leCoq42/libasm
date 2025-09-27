; strcmp(3):
; int strcmp(const char *s1, const char *s2);


section .text
global  _ft_strcmp

_ft_strcmp:
    xor rax, rax
    jmp loop

loop:




exit:
    ret