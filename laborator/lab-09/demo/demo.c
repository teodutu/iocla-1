#include <stdio.h>

int v[] = {10, 22, 39, 9, 11, 5};  // in .data

static __attribute__((always_inline)) int static_max_always_inline(int a, int b)
{
	return a > b ? a : b;
}

__attribute__((always_inline)) int max_always_inline(int a, int b)
{
	return a > b ? a : b;
}

// Nu functioneaza din cauza ca nu se defineste un simbol pentru max_inline
// Cititi sectiunea "ISO C inline semantics" din linkul de mai jos pentru detalii
// https://runtimeverification.com/blog/undefined-c-common-mistakes/
// inline int max_inline(int a, int b)
// {
// 	return a > b ? a : b;
// }

// Functioneaza pentru ca `static` restrange vizibilitatea functiei la fisierul
// curent, ceea ce forteaza compilatorul sa defineasca un simbol pentru functie
static inline int static_max_inline(int a, int b)
{
	return a > b ? a : b;
}

int main(void)
{
	int max = static_max_always_inline(5, 10);
	printf("static_max_always_inline(5, 10) = %d\n", max);

	max = max_always_inline(5, 10);
	printf("max_always_inline(5, 10) = %d\n", max);

	max = static_max_inline(5, 10);
	printf("static_max_inline(5, 10) = %d\n", max);

	int len = sizeof(v) / sizeof(*v);
	printf("len = %d\n", len);

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
