; strcpy(3):
; char *strcpy(char *restrict dst, const char *restrict src);
; 1st arg (dst) = rdi, 2nd arg (src) = rsi

global  ft_strcpy

section .text
ft_strcpy:
    xor rax, rax ; clear rax
    push rdi ; save dst pointer on stack

.loop:
    mov al, [rsi] ; load byte from src into al
    mov [rdi], al ; store byte from al into dst
    test al, al ; performs a bitwise logical AND operation between two operands
    jz .return ; jump if zero
    inc rdi ; increment dst pointer
    inc rsi ; increment src pointer
    jmp .loop ; jump to .loop

.return:
    pop rax ; restore dst pointer into rax
    ret ; return from function

section .note.GNU-stack noalloc noexec nowrite progbits
