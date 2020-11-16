%include "../utils/printf32.asm"

section .data
	a dd 0x12345678
	s db "Dorel"


section .text

extern printf
global main

main:
	mov eax, 2
	mov ebx, 3

	push eax  ; pune eax pe stiva
	; <=> sub esp, 4; mov [esp], eax
	push ebx
	; siva:
	;	eax
	;	ebx

	pop eax
	; mov eax, [esp]; add esp, 4
	pop ebx

	PRINTF32 `eax = %d | edx = %d\n\x0`, eax, ebx

	sub esp, 2
	mov [esp], word 127

	sub esp, 4
	mov [esp], dword "Gigi"

	; NU afisati esp ca il strica PRINTF32
	mov eax, esp
	PRINTF32 `stiva = %s\n\x0`, eax

	; la iesirea din functie stiva trebuie sa fie la fel ca la intrare
	add esp, 6

    ret
