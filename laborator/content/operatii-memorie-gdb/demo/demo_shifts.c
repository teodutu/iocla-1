#include <stdio.h>
#include <stdint.h>

static void print_binary(uint32_t x, size_t bits)
{
	uint32_t mask;

	printf("0b");
	for (mask = 1 << (bits - 1); mask; mask >>= 1)
		printf("%d", x & mask ? 1 : 0);
	printf("\n");
}

int main(void)
{
	uint8_t uns = 0xda;
	int8_t sgn = 0xda;

	// Unsigned shifts:
	printf("0xda = ");
	print_binary(uns, 8);

	printf("(unsigned) 0xda << 2 = ");
	print_binary(uns << 2, 8);

	printf("(unsigned) 0xda >> 3 = ");
	print_binary(uns >> 3, 8);

	// Signed shifts:
	printf("\n0xda = ");
	print_binary(sgn, 8);

	printf("(signed) 0xda << 2 = ");
	// Signed left shifts do not extend the sign.
	print_binary(sgn << 2, 8);

	printf("(signed) 0xda >> 3 = ");
	// Signed right shifts DO EXTEND THE SIGN.
	// `sgn` is signed (as seen in the binary print at line 31)
	print_binary(sgn >> 3, 8);

	// The result of the shift above needs to preserve the sign of `sgn` so
	// that the operation remains correct:
	printf("%d / 8 = %d\n", sgn, sgn >> 3);

	// Shifting by `i` is equivalent to multiplying (left shift) or
	// dividing (right shift) by 1 << i (2 to the power i):
	// a << i <=> a * (1 << i)
	// a >> i <=> a / (1 << i)
	// Hence a / 8 <=> a >> 3

	return 0;
}
