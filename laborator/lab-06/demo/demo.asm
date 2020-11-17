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

	; xchg eax, ebx
	push eax  ; <=> sub esp, 4; mov [esp], eax
	push ebx
	; stiva:
	;	eax
	;	ebx

	pop eax  ; <=> mov eax, [esp]; add esp, 4
	pop ebx

	PRINTF32 `eax = %d | edx = %d\n\x0`, eax, ebx

	; nu stie push < word
	; pt ca initial CPU era gandit pt 16b si push byte strica alinierea
	push byte 1  ; face de fapt push dword 1

	sub esp, 2
	mov [esp], word 65  ; 65 = 0x0041 -> 0x41 0x00 (l endian)

	push dword "asdf"

	; NU afisati esp; il strica PRINTF32
	mov eax, esp
	PRINTF32 `stiva = %s\n\x0`, eax

	; la iesirea din functie stiva trebuie sa fie la fel ca la intrare
	add esp, 10  ; dword + word + dword = 10B

    ret  ; <=> pop eip
