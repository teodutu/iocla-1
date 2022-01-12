#include <stdio.h>

int array_sum(int *arr, size_t len);
void print_arg(unsigned long arg);

int main(int argc, char **argv, char **envp)
{
	int arr[] = {1, 2, 3, 4, 5};
	int sum = array_sum(arr, sizeof(arr) / sizeof(*arr));	

	printf("sum = %d\n", sum);
	print_arg(20);
	print_arg(30);

	return 0;
}
