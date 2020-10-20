#include <stdio.h>
#include <stdlib.h>

int *fct_ptr(int, int);

int main(int argc, char const *argv[])
{
	int a = 10;
	void *p = &a;

	printf("*p = %d\n", *(int *)p);
	// printf("*(p + 1) = %d\n", *(p + 1));
	// *(p + 1 * sizeof(???))

	int stack[100];
	for (int i = 0; i != 100; ++i)
		stack[i] = i;

	printf("stack = %p\n", stack);
	printf("&stack = %p\n", &stack);

	int *heap = malloc(1);  // aloca pe heap
	printf("heap = %p\n", heap);  // pe heap
	printf("&heap = %p\n", &heap);  // pe stiva
	*heap = 2;
	printf("*heap = %d\n", *heap);

	// tip (*nume_ptr)(semnatura functiei)
	// tip *nume_ptr(semnatura functiei) == intoarce tip *

	int (*main_ptr)(int, char const **) = main;  // = &main (vezi liniile 19-20)
	printf("main_ptr = %p\n", main_ptr);

	return 0;
}
