; strcmp(3):
; int strcmp(const char *s1, const char *s2);


section .text
global  ft_strcmp

ft_strcmp:
    xor rax, rax
    xor rdx, rdx
    xor rcx, rcx

.loop:
    mov al, [rdi + rcx]
    mov dl, [rsi + rcx]
    cmp rax, rdx
    jne .return
    test al, al
    jz .return
    inc rcx
    jmp .loop

.return:
    sub rax, rdx
    ret
