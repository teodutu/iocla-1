%include "../utils/printf32.asm"

; variabile globale INITIALIZATE
section .data  ; rw-  -> impuse de SO
    ; dq = long = quad word
    ; dd = int = double word
    ; dw = short = word
    ; db = char(si numeric) = byte
    s db "Dorel",0
    a_int dd 10
    a_short dw 5
    a_byte db 65
    a_char db 'A'
    v_int dd 1, 2, 3, 4, 5

; variabile globale CONSTANTE
section .rodata  ; r--
    ; se declara la fel ca in .data

; variabile globale NEINITIALIZATE
; int a;  // a == 0
section .bss  ; rw-
    a resd 1  ; int a;
    b resq 10  ; long b[10];

section .text  ; r-x

extern printf
global main

main:
    push ebp
    mov ebp, esp

    mov eax, a_int  ; a_int = ptr la o zona din .data = 10
    PRINTF32 `eax = 0x%x\n\x0`, eax

    xor eax, eax
    add eax, [a_int]  ; [a_int] = *a_int
    PRINTF32 `eax = 0x%x\n\x0`, eax

    ; memoria = [ 0x05 | 0x00 | 0x41(a_byte) | 0x41(a_char) ]
    mov eax, [a_short]  ; operanzii au aceeasi dimensiune
    PRINTF32 `eax = 0x%x\n\x0`, eax

    mov [a_short], word 1024  ; ca si cum castam la word
    PRINTF32 `[a_short] = %hd\n\x0`, [a_short]

    mov ecx, 5
    xor eax, eax  ; i = 0

print_v:
    ; v[i] = v[eax] = *(v + eax * sizeof(*v))
    PRINTF32 `%d\n\x0`, [v_int + eax * 4]
    ; adresare bazata indexata si scalata
    inc eax
    cmp eax, ecx
    jne print_v

    PRINTF32 `\n\x0`

print_v_loop:
    PRINTF32 `%d\n\x0`, [v_int + ecx * 4]
    ; adresare bazata indexata, scalata si cu deplasament
    loop print_v_loop
    ; loop <=>
    ;   --ECX
    ;   if(ECX) goto print_v_loop

    ; Inmultiri
    ; mul OP2 = reg/mem
    ; R = OP1 * OP2
    ; 32b * 32b <= 64b
    ; OP1 si R sunt ficsi in fct de OP2
    ;   OP2 = 8b => OP1 = AL; R = AX
    ;   OP2 = 16b => OP1 = AX; R = DX:AX  // high = DX, low = AX
    ;   OP2 = 32b => OP1 = EAX; R = EDX:EAX
    mov ax, 0x8000
    mov bx, 0x8001
    mul bx
    ; PRINTF32 `0x%hx%hx\n\x0`, dx, ax -> ASA NU
    PRINTF32 `0x%hx%hx\n\x0`, edx, eax  ; ASA DA

    ; Impartiri cu rest
    ; D = I * C + R
    ; div I = reg/mem
    ; D, C, R sunt ficsi in fct de I
    ;   I = 8b => D = AX, C = AL, R = AH
    ;   I = 16b => D = DX:AX, C = AX, R = DX
    ;   I = 32b => D = EDX:EAX, C = EAX, R = DX

    leave
    ret
