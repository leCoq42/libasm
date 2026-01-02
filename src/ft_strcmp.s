; strcmp(3):
; int strcmp(const char *s1, const char *s2);


section .text
global  ft_strcmp

ft_strcmp:
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    jmp loop

loop:
    mov al, [rdi + rcx]
    mov bl, [rsi + rcx]
    cmp rax, rbx
    jne return
    cmp al, 0
	je return
    inc rcx
    jmp loop

return:
    sub rax, rbx
    ret
