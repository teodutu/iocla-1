#include <stdio.h>

int v[] = {10, 22, 39, 9, 11, 5};  // in .data

int main(void)
{
	int max;
	int len = sizeof(v) / sizeof(*v);

	/**
	 * Inline asm:
	 * 	- sintaxa depinde de compilator
	 * 	- folosim sintaxa GCC
	 * __asm__(
	 * 	"instructiuni asm"
	 * 	: "=r" (output1), "=m" (output2)  // = inseamna output;
	 * 		r => CPL pune output1 = reg oarecare
	 * 		m = memorie => CPL considera output2 ca fiind ptr
	 * 		output1, output2 = variabile din C
	 *  : "r" (input)  // inputuri; aceiasi specificatori ca la output
	 *  : "eax", "ebx"  // ce reg folosim in instructiuni -> sa stie CPL ce sa salveze inainte
	 * )
	 *
	 * https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html#Simple-Constraints
	 */

	// Calculam max(v)
	// NU E FUNCTIE => NU TREBUIE SA RESPECTAM NICIO CONVENTIE
	// trebuie sa lasam stiva cum era la inceput
	__asm__(
		"mov ecx, %2\n"  // ecx = len
		"mov eax, [%1]\n"  // eax = v[0]
		"dec ecx\n"  // parcurg v[5] -> v[1]
		"compute_max:\n"
		"cmp eax, [%1 + ecx * 4]\n"  // %1 e tot un reg
		"jge continue\n"
		"mov eax, [%1 + ecx * 4]\n"
		"continue:\n"
		"loop compute_max\n"
		"mov %0, eax\n"  // CPL face si trecerea de la reg %0 la variabila max
		: "=r" (max)  // output; max = %0
		: "r" (v), "r" (len)  // input; v = %1; len = %2
		: "ecx", "eax"
	);

	// lea eax, [eax * 2] <=> eax *= 2; lea = load effective address

	printf("max = %d\n", max);

	// Pt ex 6+ -> param pe 64 NU se pun pe stiva ci in reg:
	//		RDI, RSI, RDX, RCX, R8, R9

	return 0;
}
