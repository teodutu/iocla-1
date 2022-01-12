#include <stddef.h>

int array_sum(int *arr, size_t len)
{
	size_t i;
	int sum = 0;

	for (i = 0; i != len; sum += arr[i++]);

	return sum;
}
