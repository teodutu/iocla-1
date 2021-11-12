%include "../io.mac"

global main
extern printf

section .rodata
	printed db 'This should be printed', 10, 0		; 10 = \n in ASCII
	not_printed db 'This should NOT be printed', 10, 0	; 10 = \n in ASCII

section .text
main:
	; <menmonica> dest, src
	mov eax, 0x12345678
	mov eax, 1337		; eax = 1337
	mov ebx, eax		; ebx = eax

	PRINTF32 `eax = %d, ebx = %d\n\x0`, eax, ebx

	mov eax, 1
	mov ebx, 2
	add eax, ebx		; eax += ebx
	PRINTF32 `eax = 1 + 2 = %d\n\x0`, eax
	; sub, and, or, xor, not (~)
	; exista si mul (*), div (/): TBC

	mov eax, 4
	shr eax, 2		; eax >>= 2
	PRINTF32 `eax = 4 >> 2 = %d\n\x0`, eax

	shl eax, 3		; eax <<= 3
	PRINTF32 `eax = 1 << 3 = %d\n\x0`, eax

	; EFLAGS - doar pt operatii matematice
	;	- ZF = zero flag = ultima operatie a dat 0; ex: `xor eax, eax`
	;	- SF = sign flag = ultima operatie a activat bitul de semn
	;	- CF = carry flag = ultima operatie a depasit dimensiunea registrului
	;
	; j[n]<flag> addr <=> if ([not] <flag>) jmp addr

	mov eax, 1
	sub eax, 2
	js sign

	PRINTF32 `sign - %s\x0`, not_printed

sign:
	PRINTF32 `sign - %s\x0`, printed

	mov al, 200
	add al, 100
	jc carry

	PRINTF32 `carry - %s\x0`, not_printed

carry:
	PRINTF32 `carry - %s\x0`, printed

	; cmp
	mov eax, -1		; 0xffffffff
	mov ebx, 2		; 0x00000002
	cmp eax, ebx		; CPU-ul seteaza EFLAGS conform cu `eax - ebx` 
	jl smaller

	; jb (jump below) -> UNISGNED
	; jl (jump lower) -> SIGNED
	; jb/ja = below/above = </> UNSIGNED
	; jl/jg = lower/greater = </> SIGNED

	PRINTF32 `smaller - %s\x0`, not_printed

smaller:
	PRINTF32 `smaller - %s\x0`, printed

	xor eax, eax
	ret
