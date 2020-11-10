%include "../utils/printf32.asm"

; var globale INITIALIZATE
; int a_dword = 2;
; short a_short = 3;
; uint8_t a_byte = 65;
section .data  ; rw- -> gestionate de SO (pot fi schimbate de mana)
    ; db = define byte -> 8b
    ; dw -> word = 16b
    ; dd -> double word = 32b
    ; dq -> quad word = 64b
    s db "Dorel", 0  ; 0 == '\0'
    ; <=> s db 'D', 'o', 'r', 'e', 'l', 0
    a_dword dd 2
    a_word dw 3
    a_char db 'A'
    a_byte db 65
    a resd 3  ; echivalent cu a-l declara in bss
    v_int dd 1, 2, 3, 4, 5

; var globale CONSTANTE
section .rodata  ; r--
; fix la fel ca .data

; var globale NEINITIALIZATE;
; int a;  // a = 0;
; nu tine datele in executabil; datele sunt scrise direct in RAM la rulare.
section .bss  ; rw-
    b_dword resd 2  ; int b_dword[2]
    b_byte resb 10  ; char b_byte[10];
    ; resw, resq

; cod executabil
section .text  ; r-x

extern printf
global main

main:
    push ebp
    mov ebp, esp

    mov eax, a_dword  ; a_dword = ptr la un int din .data care e = 2
    PRINTF32 `eax = 0x%x\n\x0`, eax

    mov eax, [a_dword]  ; [a_dword] = *(int *)a_dword
    PRINTF32 `[a_word] = 0x%x\n\x0`, eax

    ; memoria = [ 0x05 | 0x00 | 0x41(a_byte) | 0x41(a_char) ]
    mov eax, [a_short]  ; operanzii au aceeasi dimensiune
    ; => eax = 0x41410005
    PRINTF32 `eax = 0x%x\n\x0`, eax

    mov [a_word], word 20  ; ca si cum castam la word
    PRINTF32 `[a_word] = %hd\n\x0`, [a_word]

    mov ecx, 5
    xor eax, eax  ; int i = 0;

print_v:
    ; v[i] = v[eax] = *(v + eax * sizeof(*v))
    PRINTF32 `%d \x0`, [v + eax * 4]
    ; adresare bazata indexata si scalata (denumire cretina; nu va trebuie la lab)
    inc eax
    cmp eax, ecx
    jne print_v

    PRINTF32 `\n\x0`

print_v_loop:
    PRINTF32 `%d \x0`, [v + (ecx - 1) * 4]  ; <=> [v + ecx * 4 - 4]
    ; adresare bazata indexata, scalata si cu deplasament (alta denumire idioata)
    loop print_v_loop
    ; loop label <=>
    ;   --ECX
    ;   if (ECX) goto label

    PRINTF32 `\n\x0`

    ; Inmultirea
    ; R = OP1 * OP2
    ; 32b * 32b <= 64
    ; mul op2 -> reg/mem
    ; OP1 se ia in fct de OP2
    ;   OP2 = 8b => OP1 = AL; R = AX
    ;   OP2 = 16b => OP1 = AX; R = DX:AX (high = DX; low = AX)
    ;   OP2 = 32b => OP1 = EAX; R = EDX:EAX (high = EDX; low = EAX)
    mov ax, [a_word]
    mov bx, 3
    mul bx
    PRINTF32 `ax = %d\n\x0`, eax  ; PRINTF32 DOAR CU OPERANZI DE 32b

    mov eax, 2
    mov ebx, 3
    imul eax, ebx  ; eax *= ebx
    PRINTF32 `eax = %d\n\x0`, eax

    ; Impartirea cu REST
    ; D = I * C + R
    ; div I -> reg/mem
    ; C si R se pun si D se ia in fct de I
    ;   I = 8b => D = AX; C = AL; R = AH
    ;   I = 16b => D = DX:AX; C = AX; R = DX
    ;   I = 32b => D = EDX:EAX; C = EAX; R = EDX
    mov ax, 5
    mov bl, 2
    div bl
    PRINTF32 `C,R = %hx\n\x0`, eax

    leave
    ret
