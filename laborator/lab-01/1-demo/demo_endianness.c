#include <stdio.h>

int main(int argc, char const *argv[])
{
	int x = 0x12345678;
	printf("&x = %p\n", &x);

	char *p = &x;
	printf("p: %p -> 0x%x\n", p, *p);
	printf("(p + 1): %p -> 0x%x\n", (p + 1), *(p + 1));
	printf("(p + 2): %p -> 0x%x\n", (p + 2), *(p + 2));
	printf("(p + 3): %p -> 0x%x\n", (p + 3), *(p + 3));

	short *q = &x;  // sizeof(short) == 2
	printf("q: %p -> 0x%x\n", q, *q);
	printf("(q + 1): %p -> 0x%x\n", (q + 1), *(q + 1));

	// v[i] == *(v + i) == "*(v + i * sizeof(*v))"
	printf("sizeof(q) = %zu\n", sizeof(q));
	printf("sizeof(*q) = %zu\n", sizeof(*q));

	return 0;
}
