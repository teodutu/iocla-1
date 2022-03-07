#include <stdio.h>

int main(void)
{
	char s[] = {0x12, 0x34, 0x56, 0x78};
	int x = 0x12345678;
	char *p_char;
	short int *p_short;
	size_t i;

	printf("s =\n");
	p_char = s;
	for (i = 0; i != sizeof(s); ++i) {
		printf("%p -> 0x%hhx\n", p_char, *p_char);
		p_char++;
	}
	printf("\n");

	printf("x =\n");
	p_char = (char *)&x;
	for (i = 0; i != sizeof(x); ++i) {
		printf("%p -> 0x%hhx\n", p_char, *p_char);
		p_char++;
	}
	printf("\n");

	printf("x 2 bytes at a time:\n");
	p_short = (short int*) &x;
	printf("%p -> 0x%hx\n", p_short, *p_short);
	p_short++;
	printf("%p -> 0x%hx\n", p_short, *p_short);

	return 0;
}
