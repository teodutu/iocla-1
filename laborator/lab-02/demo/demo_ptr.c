#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global[100];

int *f() {
	int x = 10;
	// Compilatorul se prinde ca e prost ce fac => schimba
	// codul ca sa return NULL
	return &x;
}

int main(int argc, char const *argv[])
{
	int a = 10;

	// Pt compilator: stack ~ label pt zona de memorie
	int stack[100];
	printf("&stack = %p\n", &stack);
	printf("stack = %p\n", stack);

	printf("&global = %p\n", &global);
	printf("global = %p\n", global);

	// SO ii da unui proces memorie (cel putin cata cere)
	// SO aloca mult mai mult heap decat 1 byte
	int *p = malloc(1);
	*p = 2;
	printf("&p = %p\n", &p);
	printf("p = %p\n", p);
	printf("*p = %d\n", *p);

	// int *main_ptr(int, const char **) == declarare de functie
	int (*main_ptr)(int, const char **) = main;  // sau &main
	printf("&main_ptr = %p\n", &main_ptr);
	printf("main_ptr = %p\n", main_ptr);

	printf("%p\n", f());

	sleep(1);
	(*main_ptr)(0, NULL);

	return 0;
}
