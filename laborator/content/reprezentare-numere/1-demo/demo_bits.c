#include <stdio.h>

int main(void)
{
	/*
	0b1100 = 0xc
	0b1001 = 0x9

	4 biti = nibble -> o litera hexa
	8 biti = byte / octet

	https://www.rapidtables.com/convert/number/hex-to-binary.html

	Op pe biti:
	! (not):
	a = 1 => !a = 0
	a = -2 => !a = 0

	~ (neg): neaga bitii
	a = 0b0010 => ~a = 0b1101
	a = 0b1010 => ~a = 0b0101

	&:
	a - 1 bit
	a & 0 = 0
	a & a = a

	a % 2 == 1 <=> a & 1
	a = 0b...1 => a % 2 == 1 == a & 1
	a = 0b...0 => a % 2 == 0 == a & 1

	|:
	a - 1 bit
	a | 1 = 1
	a | 0 = a

	^:
	1 ^ 1 = 0
	1 ^ 0 = 1
	a ^ a = 0
	a = 0 <=> a ^= a
	a == b <=> !(a ^ b) <- pt ex 2
	*/

	// 0b000001 => 0b001000
	int x = 1 << 4;  // 1 << n <=> pow(2, n);
	printf("1 << 4 == %d\n", x);

	// 0b00...1
	int int_x = 1 << 32;
	printf("1 << 32 == %d\n", int_x);

	printf("sizeof(long) = %zu\n", sizeof(long));

	// calculul se face pe int pt ca 1 e int
	long long_x = 1 << 32;
	printf("(long) 1 << 32 == %ld\n", long_x);

	// calculul se face pe long pt ca 1L e long
	long long_x_L = 1L << 32;
	printf("(long) 1L << 32 == %ld\n", long_x_L);

	// 0U; 42LLU

	// ordinea operatiilor: *, /	+, -	&, |, ^, <<, >>
	// https://en.cppreference.com/w/c/language/operator_precedence
	// 1 + 1 << 2 <=> (1 + 1) << 2
	int a = 1 + 1 << 2;
	printf("1 + 1 << 2 == %d\n", a);

	int a_correct = 1 + (1 << 2);
	printf("1 + (1 << 2) == %d\n", a_correct);

	return 0;
}
