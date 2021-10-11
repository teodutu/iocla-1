%include "../io.mac"

section .text
    global main
    extern printf

main:
    mov eax, 1
    mov ebx, 1
    mov ecx, 1
    cmp eax, ebx                ; ZF == 1
    add ecx, 1                  ; add seteaza si el acelasi EFLAGS
    je print
    ret

print:
    PRINTF32 `%d\n\x0`, eax
    ret
