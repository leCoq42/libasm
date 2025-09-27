global  _start

section .text
_start:
    xor rax, rax
    jmp loop

loop:
    cmp BYTE [rdi + rax], 0
    jz ret
    inc rax
    jmp loop