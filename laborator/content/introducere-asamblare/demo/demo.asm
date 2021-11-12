%include "../io.mac"

global main
extern printf

section .rodata
	printed db 'This should be printed', 10, 0		; 10 = \n in ASCII
	not_printed db 'This should NOT be printed', 10, 0	; 10 = \n in ASCII

section .text
main:
	; mov dest, src
	mov eax, 0x12345678
	mov eax, 1337		; eax = 1337
	mov ebx, eax		; ebx = eax

	PRINTF32 `eax = %d, ebx = %d\n\x0`, eax, ebx

	; operatii
	mov eax, 1
	mov ebx, 2
	add eax, ebx
	PRINTF32 `eax = 1 + 2 = %d\n\x0`, eax

	mov eax, 3
	mov ebx, 2
	sub eax, ebx
	PRINTF32 `eax = 3 - 2 = %d\n\x0`, eax

	mov eax, 4
	shr eax, 2		; eax >> 2
	PRINTF32 `eax = 4 >> 2 = %d\n\x0`, eax

	shl eax, 3		; eax << 3
	PRINTF32 `eax = 1 << 3 = %d\n\x0`, eax

	mov eax, 3
	and eax, 2		; or, xor, not
	PRINTF32 `eax = 3 & 2 = %d\n\x0`, eax

	jmp skip
	PRINTF32 `%s\x0`, not_printed
skip:
	PRINTF32 `%s\x0`, printed

	; EFLAGS:
	;	- ZF = zero flag = cand ultima operatie a dat 0
	;	- SF = sign flag = cand ultima operatie a activat bitul de semn
	;	- CF = carry flag = se depaseste dimensiunea registrului
	;
	; j[n]<flag> addr = if ([!]<flag>) jmp addr

	; CF
	mov al, 200
	mov bl, 100
	add al, bl
	jc carry

	PRINTF32 `%s\x0`, not_printed
carry:
	PRINTF32 `%s\x0`, printed

	mov eax, 1
	mov ebx, -2
	cmp eax, ebx		; "in spate": tmp = eax - ebx 
	jg exit

	PRINTF32 `%s\x0`, not_printed

exit:
	PRINTF32 `%s\x0`, printed

	; jl/jg = </> CU SEMN
	; jb/ja = </> FARA SEMN

	xor eax, eax
	ret
