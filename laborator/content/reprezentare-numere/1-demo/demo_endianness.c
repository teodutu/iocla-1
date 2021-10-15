#include <stdio.h>

int main(void)
{
	int x = 0x12345678;  // x = [0x78, 0x56, 0x34, 0x12] -> in memorie
	printf("&x = %p\n", &x);

	char *p = (char *)&x;
	printf("(p + 0): %p -> 0x%x\n", p, *p);
	printf("(p + 1): %p -> 0x%x\n", (p + 1), *(p + 1));
	printf("(p + 2): %p -> 0x%x\n", (p + 2), *(p + 2));
	printf("(p + 3): %p -> 0x%x\n", (p + 3), *(p + 3));

	short *q = (short *)&x;
	printf("%p -> 0x%x\n", q, *q);
	printf("%p -> 0x%x\n", q + 1, *(q + 1));

	// v[i] == *(v + i) == "*(v + i * sizeof(*v))"

	printf("sizeof(q) = %zu\n", sizeof(q));
	printf("sizeof(*q) = %zu\n", sizeof(*q));

	return 0;
}
