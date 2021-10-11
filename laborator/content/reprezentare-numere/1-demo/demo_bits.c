#include <stdio.h>

int main(int argc, char const *argv[])
{
	int x = 1 << 4;  // 1 << a == pow(2, a)
	printf("x = %d\n", x);  // n = 0b00001110; n << 2 = 0b00111000

	int int_x = 1 << 32;  // 1 = 0b000...01; 1 << 32 = 0
	printf("int_x = %d\n", int_x);

	long long long_long_x = 1 << 32;  // shiftarea se efectueaza pe int pt ca 1 e int
	printf("long_long_x = %lld\n", long_long_x);

	long long long_long_x_correct = 1LL << 32;  // 1LL == (long long)1
	printf("long_long_x_correct = %lld\n", long_long_x_correct);

	// Precedenta <=> ordinea efectuarii operatiilor
	// in ordinea: *, /;    +, -;     &, |, ^, <<, >>
	int y = 1 + 1 << 3;  // == (1 + 1) << 3
	printf("1 + 1 << 3 = %d\n", y);

	int z = 1 + (1 << 3);
	printf("1 + (1 << 3) = %d\n", z);

	return 0;
}
