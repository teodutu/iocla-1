%include "../utils/printf32.asm"


section .data
	v dw 3, 3, 4, 2, 2, 5, 1, 2, 3, 1
	len dd 10

section .text

extern printf
global main


; int compute_occurrences(short el, short *v, int len)
; folosim calling conventionul "cdecl":
;	- parametrii se pun de catre apelant (main) pe stiva
;	- val intoarsa = eax
;	- fct apelata trebuie sa pastreze ebx la fel cand incepe si cand se termina
;	- fct apelanta pune si scoate param de pe stiva

; stiva:
;	len
;	v
;	el
compute_occurrences:
	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main) <- esp

	; salvez si stiva lui main
	push ebp
	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main)
	; 	ebp_main <- esp

	mov ebp, esp
	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main)
	; 	ebp_main <- esp, ebp
	;--------------------------- -> de aici in jos e stiva lui compute_occurrences

	sub esp, 4  ; int no_occ
	; stiva:
	;	[len] (int) <- ebp + 14
	;	v (short *) (4B pt ca e ptr) <- ebp + 10
	;	el (short) <- ebp + 8
	;	eip_leave (main) <- ebp + 4
	; 	ebp_main <- ebp
	;---------------------------
	;	no_occ <- esp

	mov dword [ebp - 4], 0  ; no_occ = 0

	mov edi, [ebp + 10]  ; v
	mov ecx, [ebp + 14]  ; len
	mov ax, [ebp + 8]  ; el; mereu primul param -> ebp + 8

compute_occ:
	cmp ax, [edi + (ecx - 1) * 2]
	jne continue

	inc dword [ebp - 4]  ; no_occ++

continue:
	loop compute_occ

	mov eax, [ebp - 4] ; prin conventie -> val intoarsa = eax

	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main)
	; 	ebp_main <- ebp
	;---------------------------
	;	no_occ <- esp
	mov esp, ebp

	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main)
	; 	ebp_main <- ebp, esp
	pop ebp

	; stiva:
	;	[len]
	;	v
	;	el
	;	eip_leave (main) <- esp
	ret  ; <=> pop eip

main:
	push ebp
	mov ebp, esp

	sub esp, 20  ; var locale

	; enter x, 0
	; <=>
	;  push ebp
	;  mov ebp, esp
	;  sub esp, x

	push dword [len]
	push v	; v == ptr la vector
	push word 2
	call compute_occurrences
	; <=>
	;  push eip_prima_instr_de_dupa_call
	;  jmp compute_occurrences

	; stiva:
	;	[len]
	;	v
	;	el

	; e bine sa scoatem param de pe stiva
	; nu e obligatoriu
	add esp, 10  ; sizeof(*len) + sizeof(v) + sizeof(el)
	; nu vreau sa scot si var locale de pe stiva

	PRINTF32 `numarul de aparitii = %d\n\x0`, eax

	leave
	; <=>
	;  mov esp, ebp
	;  pop ebp

	ret
