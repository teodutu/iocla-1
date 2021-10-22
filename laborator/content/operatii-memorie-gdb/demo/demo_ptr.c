#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Pointer in .data; string in .rodata
char *global_ct_str = "manele";

// .data
// Desi au aceeasi valoare, stringurile sunt zone diferite de memorie,
// pentru ca nu sunt constante 
char global_str1[] = "florin salam";
char global_str2[] = "florin salam";

int main(int argc, char const **argv)
{
	// https://i.stack.imgur.com/9ZHwD.png

	int a = 10; // pe stiva
	printf("&a = %p\n", &a);
	printf("a = %d\n\n", a);

	printf("&global_ct_str = %p\n", &global_ct_str);
	printf("global_ct_str = %p\n\n", global_ct_str);

	global_ct_str = "florin salam";
	printf("global_ct_str = %p\n\n", global_ct_str);

	// Pointer pe stiva, string in .rodata
	char *stack_ct_str = "manele";
	printf("&stack_ct_str = %p\n", &stack_ct_str);
	printf("stack_ct_str = %p\n\n", stack_ct_str);

	printf("&global_str1 = %p\n", &global_str1);
	printf("global_str1 = %p\n\n", global_str1);
	printf("&global_str2 = %p\n", &global_str2);
	printf("global_str2 = %p\n\n", global_str2);

	// Array-urile statice sunt doar labeluri pt zona de memorie
	// "florin salam" e pus pe stiva
	char stack_str[] = "florin salam";
	printf("&stack_str = %p\n", &stack_str);
	printf("stack_str = %p\n\n", stack_str);

	int *heap_ptr = malloc(1);  // aloc 1 byte
	// SO aloca mai mult heap la inceputul rularii => nu da seg fault.
	heap_ptr[1000] = 2;
	printf("&heap_ptr = %p\n", &heap_ptr);
	printf("heap_ptr = %p\n", heap_ptr);
	printf("heap_ptr[1000] = %d\n\n", heap_ptr[1000]);

	int (*mai_ptr)(int, char const **) = main;
	printf("&main_ptr = %p\n", &mai_ptr);
	printf("main_ptr = %p\n\n", mai_ptr);

	printf("printf = %p\n\n", printf);

	sleep(5);
	mai_ptr(0, NULL);

	// sleep(1000);

	return 0;
}
