#include <stdio.h>

int v[] = {10, 22, 39, 9, 11, 5};  // in .data

int main(void)
{
	int len = sizeof(v) / sizeof(*v);
	printf("%d\n", len);

	int max;

	// In general, sintaxa pentru inline asm depinde de compilator
	// Mai jos e sintaxa pentru GCC

	// Calculam max(v)
	// NU E FUNCTIE => nu trebuie respectata conventia _cdecl
	// trebuie sa lasam stiva cum era la inceput
	__asm__(
		// %2 = parametrul 2 dat ca out/in
		"mov ecx, %2\n"  // ecx = len
		"mov eax, [%1]\n"  // %1 = v
		"dec ecx\n"
		"compute_max:\n"
		"cmp eax, [%1 + ecx * 4]\n"
		"jge continue\n"
		"mov eax, [%1 + ecx * 4]\n"
		"continue:\n"
		"loop compute_max\n"
		"mov %0, eax\n"  // %0 = max
		: "=r" (max)  // OUTPUT; r -> CPL o sa puna max intr-un reg oarecare
		// r => ne referim la param respectiv ca si cum ar fi un registru oarecare
		// m => ne referim la param respectiv ca si cum ar fi pointer (memorie)
		: "m" (v), "r" (len)  // INPUT
		: "eax", "ecx"  // specificam ce registre folosim in codul de mai sus
	);

	printf("max = %d\n", max);

	// param pe 64 nu se pun pe stiva, ci in registre, in ordinea asta:
	//	rdi, rsi, rdx, rcx, r8, r9, urmatorii pe stiva
	//	r8 - r15 = reg noi pe 64b, r8d = 32b; r8w = 16b

	return 0;
}
