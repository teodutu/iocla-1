#include <stdio.h>

void print_arg(unsigned long arg)
{
	static int x;
	x++;

	printf("x = %d; 0x%lx\n", x, arg);
}
