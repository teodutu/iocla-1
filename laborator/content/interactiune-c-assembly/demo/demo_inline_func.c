#include <stdio.h>

// Nu functioneaza din cauza ca nu se defineste un simbol pentru max_inline
// Cititi sectiunea "ISO C inline semantics" din linkul de mai jos pentru detalii
// https://runtimeverification.com/blog/undefined-c-common-mistakes/
// inline int max_inline(int a, int b)
// {
// 	return a > b ? a : b;
// }

// Functioneaza pentru ca `static` restrange vizibilitatea functiei la fisierul
// curent, ceea ce forteaza compilatorul sa defineasca un simbol pentru functie
static inline int max(int a, int b)
{
	return a > b ? a : b;
}

int main(void)
{
	printf("max(2, 5) = %d\n", max(2, 5));
	return 0;
}
