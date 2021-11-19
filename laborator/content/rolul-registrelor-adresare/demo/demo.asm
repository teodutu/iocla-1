%include "../utils/printf32.asm"

; var globale INITIALIZATE
section .data       ; rw-
    ; db = define byte -> 8b
    ; dw -> word = 16b
    ; dd -> double word = 32b
    ; dq -> quad word = 64b
    a_word dw 0x1337
    a_byte db 65
    a_char db 'B'
    a_string db 'manele', 10, 0     ; 10 = \n in ASCII; 0 = \0
    ; <=> a_string db 'm', 'a', 'n', 'e', 'l', 'e', 10, 0
    a_dword dd 10000000

; var globale CONSTANTE
section .rodata     ; r--
; fix la fel ca .data
    ints dd 10, 32, 11, 20

; var globale NEINITIALIZATE;
; int a;  // a = 0;
; nu tine datele in executabil; datele sunt scrise direct in RAM la rulare.
section .bss  ; rw-
    b_dword resd 2  ; int b_dword[2]
    b_byte resb 10  ; char b_byte[10];
    ; resw, resq

; cod executabil
section .text       ; r-x

extern printf
global main

main:
    push ebp
    mov ebp, esp

    ; Inmultire
    ; R = OP1 * OP2
    ; 32b * 32b <= 64
    ; mul op2 -> reg/mem
    ; OP1 se ia in fct de OP2
    ;   OP2 = 8b => OP1 = AL; R = AX
    ;   OP2 = 16b => OP1 = AX; R = DX:AX (high = DX; low = AX)
    ;   OP2 = 32b => OP1 = EAX; R = EDX:EAX (high = EDX; low = EAX)
    mov bx, 2000
    mov ax, 1000
    mul bx      ; rezultat = DX:AX

    shl edx, 16
    mov dx, ax

    PRINTF32 `edx = %d\n\x0`, edx

    ; Impartire cu REST
    ; D = I * C + R
    ; div I -> reg/mem
    ; C si R se pun si D se ia in fct de I
    ;   I = 8b => D = AX; C = AL; R = AH
    ;   I = 16b => D = DX:AX; C = AX; R = DX
    ;   I = 32b => D = EDX:EAX; C = EAX; R = EDX
    mov ax, 16
    mov bl, 5
    div bl      ; R = AH; C = AL

    PRINTF32 `C = %hhd\n\x0`, eax
    shr ax, 8
    PRINTF32 `R = %hhd\n\x0`, eax

    ; --------------------------------------------
    ; Adresare:
    mov eax, a_dword
    PRINTF32 `a_dword = 0x%x\n\x0`, eax

    mov eax, [a_dword]
    PRINTF32 `*a_dword = %d\n\x0`, eax

    mov eax, [a_word]
    PRINTF32 `*a_word = %x\n\x0`, eax

    ; memoria = [ 0x37 | 0x13 | 0x41(a_byte) | 0x42(a_char) ]
    mov [a_word], word 10
    PRINTF32 `*a_word = %hd\n\x0`, [a_word]

    mov ecx, 4

    lea eax, [ints + (ecx - 1) * 4]     ; lea calculeaza
    PRINTF32 `*eax = %d\n\x0`, [eax]

    mov ecx, 4
    xor eax, eax  ; int i = 0;

print_ints:
    ; v[i] = v[eax] = *(ints + eax * sizeof(*v))
    PRINTF32 `%d \x0`, [ints + eax * 4]
    ; adresare bazata, indexata si scalata (denumire cretina; nu va trebuie la lab)
    inc eax
    cmp eax, ecx
    jne print_ints

    PRINTF32 `\n\x0`

print_ints_loop:     ; ecx = [4..1]
    ; ints[ecx] = *(ints + ecx * sizeof(*ints))
    ; adresare bazata, indexata, scalata cu deplasament (limbaj de lemn...)
    mov edx, [ints + (ecx - 1) * 4]
    PRINTF32 `%d \x0`, edx
    loop print_ints
    ; loop label <=>
    ;   dec ECX
    ;   jnz label

    PRINTF32 `\n\x0`

    leave
    ret
