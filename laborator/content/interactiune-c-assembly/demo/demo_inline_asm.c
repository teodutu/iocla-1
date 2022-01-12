#include <stdio.h>

int v[] = {10, 11, 12};  // in .data

int main(void)
{
	size_t len = sizeof(v) / sizeof(*v);
	int sum;

	// In general, sintaxa pentru inline asm depinde de compilator
	// Mai jos e sintaxa pentru GCC

	// Calculam sum(v)
	// NU E FUNCTIE => nu trebuie respectata conventia _cdecl
	// ar fi bine sa lasam stiva cum era la inceput
	__asm__(
		// %2 = parametrul 2 dat ca out/in
		"xor %0, %0\n"  // sum = 0
		"compute_sum:\n"
		"add %0, [%1 + %2 * 4 - 4]\n"
		"loop compute_sum\n"
		: "=r" (sum)  // OUTPUT; r -> CPL o sa puna sum intr-un reg oarecare
		// r => ne referim la param respectiv ca si cum ar fi un registru oarecare
		// m => ne referim la param respectiv ca si cum ar fi pointer (memorie)
		: "m" (v), "c" (len)  // INPUT
		:  // specificam ce registre folosim in codul de mai sus
	);

	printf("sum = %d\n", sum);

	// param pe 64 nu se pun pe stiva, ci in registre, in ordinea asta:
	//	rdi, rsi, rdx, rcx, r8, r9, urmatorii pe stiva
	//	r8 - r15 = reg noi pe 64b
	//	r8d = 32b; r8w = 16b; r8b = 8b; analog pentru restul registrelor "noi"

	return 0;
}
