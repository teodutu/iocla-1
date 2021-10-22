#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// array static == label => totul e in .data
char global_str1[] = "manele";
char global_str2[] = "manele";

// pointer in .data; valoare in .rodata
int *global_int = 1;
char *global_ct_str = "manele";

int global_a = 0x12345678;  // in .data
const int global_const_a = 0x12345678;  // in .rodata


int main(int argc, char const **argv)
{
	// https://i.stack.imgur.com/9ZHwD.png

	int a = 10; // pe stiva
	printf("&a = %p\n", &a);
	printf("a = %d\n\n", a);

	printf("&global_ct_str = %p\n", &global_ct_str);
	printf("global_ct_str = %p\n\n", global_ct_str);

	// Pointer pe stiva, string in .rodata
	char *stack_str = "manele";
	printf("&stack_str = %p\n", &stack_str);
	printf("stack_str = %p\n\n", stack_str);

	printf("&global_str1 = %p\n", &global_str1);
	printf("global_str1 = %p\n\n", global_str1);

	printf("&global_str2 = %p\n", &global_str2);
	printf("global_str2 = %p\n\n", global_str2);

	printf("&global_int = %p\n", &global_int);
	printf("global_int = %p\n\n", global_int);

	int *heap_ptr = malloc(1);  // aloc 1 byte
	// SO aloca mai mult heap la inceputul rularii => nu da seg fault.
	heap_ptr[1000] = 2;
	printf("&heap_ptr = %p\n", &heap_ptr);
	printf("heap_ptr = %p\n", heap_ptr);
	printf("heap_ptr[1000] = %d\n\n", heap_ptr[1000]);

	int (*main_ptr)(int, char const **) = main;
	printf("&main_ptr = %p\n", &main_ptr);
	printf("main_ptr = %p\n\n", main_ptr);

	printf("printf = %p\n\n", printf);

	int b = 0x12345678;  // pe stiva (RW)
	const int stack_b = 0x12345678;  // pe stiva (RW)
	// Aici `const` nu inseamna nimic dupa compilare pentru ca permisiunile
	// stivei sunt RW.
	// La variabilele globale const are sens si la rulare pentru ca .rodata
	// si .data sunt zone diferite.

	global_ct_str = "manele 2022";

	// Pentru ca `global_str1` e doar un label si desemneaza o zona de
	// memorie, compilatorul ii stie dimensiunea. 
	printf("sizeof(global_str1) = %zu\n", sizeof(global_str1));

	// Compilatorul calculeaza ce stie la runtime la ce pointeaza
	// `global_ct_str`: la "manele", "manele 2022" sau altceva?
	printf("sizeof(global_ct_str) = %zu\n", sizeof(global_ct_str));

	return 0;
}
