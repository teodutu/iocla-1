%include "../utils/printf32.asm"


section .text

extern printf
extern exit

global main

main:
	mov ebp, esp

	mov eax, 2
	mov ebx, 3

	; xchg eax, ebx
	; push eax
	; mov eax, ebx
	; pop ebx
	push eax
	push ebx
	; stiva:
    ;       eax
    ;       ebx
	pop eax
	pop ebx

	PRINTF32 `eax = %d, ebx = %d\n\x0`, eax, ebx

	; CPU nu stie push < word
    ; pt ca initial CPU era gandit pt 16b si push byte strica alinierea
    push byte 20  ; face de fapt push dword 20: lungimea cuvantului = 4B

	; [0x41 | 0x00] -> se pun 2B pe stiva
	push word 0x41

	; NU afisati nimic prin esp; il strica PRINTF32
	mov eax, esp
	PRINTF32 `esp = 0x%hx\n\x0`, dword [eax]

	; [a b c d]
	push 'abcd'

	mov eax, esp
	PRINTF32 `esp = %s\n\x0`, eax

	; la iesirea din functie stiva trebuie sa fie la fel ca la intrare
    ; add esp, 10  ; dword + word + dword = 10B
	mov esp, ebp  ; mai elegant

	ret ; <=> pop eip
