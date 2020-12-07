%include "../utils/printf32.asm"

struc demo_struct
	short_y resw 1
	int_x resd 1
	str_z resb 100
endstruc

section .data
	fmt_hex db "%x", 10, 0
	fmt_int db "%d", 10, 0
	fmt_str db "%s", 10, 0

	demo:
		istruc demo_struct
			at short_y, dw 0xabcd
			at int_x, dd 0x12345678
			at str_z, db "Manele 2021", 0
		iend
	; [0xcd | 0xab | 0x78 | 0x56 | 0x34 | 0x12 | "Manele 2021", 0]

section .text

extern printf
global main

main:
    push ebp
    mov ebp, esp

	push int_x
	push fmt_int
	call printf

	push short_y
	push fmt_int
	call printf

	push str_z
	push fmt_int
	call printf

	; sizeof(struct demo_struct)
	; pt orice struct, NASM defineste <nume_struct>_size
	push demo_struct_size
	push fmt_int
	call printf

	push dword [demo + int_x]
	push fmt_hex
	call printf

	xor eax, eax
	mov ax, [demo + short_y]
	push eax
	push fmt_hex
	call printf

	push dword demo + str_z
	push fmt_str
	call printf

    leave
    ret
