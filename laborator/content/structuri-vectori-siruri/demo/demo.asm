%include "../utils/printf32.asm"

struc demo_struct
	short_y resw 1
	int_x resd 1
	str_z resb 100
endstruc
; [ short_y (2B) | int_x (4B) | "Manele 2022\0" ]

; in C:
; struct demo_struct2 {
;   int int_x;
;   short short_y;
;   long long long_z;
; } => compilatorul pune padding => sizeof(struct demo_struct2) = 16
; [ int_x (4B) | short_y (2B) | padding (nimic) (2B) | long_z (8B) ]
section .data
	demo:
		istruc demo_struct
			at short_y, dw 0xabcd
			at 2, dd 0x12345678
			at str_z, db "Manele 2022", 0
		iend
	; [0xcd | 0xab | 0x78 | 0x56 | 0x34 | 0x12 | "Manele 2022\0" 0, 0, ... (pana la 100B)]

	arr: dd 1, 22, 32, 45

section .text

extern printf
global main

; void print_pos(int *arr, int pos)
print_pos:
    push ebp
    mov ebp, esp

	mov eax, [ebp + 8]		; arr -> ebp + 8
	mov ecx, [ebp + 12]		; pos -> ebp + 12

	PRINTF32 `arr[pos] = %d\n\x0`, [eax + ecx * 4]		; arr[pos]

	mov dword [eax + ecx * 4], 8

	PRINTF32 `arr[pos] = %d\n\x0`, [eax + ecx * 4]

	leave
    ret


main:
    push ebp
    mov ebp, esp

	PRINTF32 `int_x = %d\n\x0`, int_x
	PRINTF32 `str_z = %d\n\x0`, str_z

	mov eax, [demo + int_x]
	PRINTF32 `demo.int_x = 0x%x\n\x0`, eax

	push 2
	push arr
	call print_pos

    leave
    ret
