; strcmp(3):
; int strcmp(const char *s1, const char *s2);


section .text
global  _ft_strcmp

_ft_strcmp:
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    jmp loop

loop:
    mov rax, [rdi + rcx]
    mov rbx, [rsi + rcx]
    cmp rax, rbx
    jne return
    inc rcx
    jmp loop

return:
    sub rax, rbx
    ret