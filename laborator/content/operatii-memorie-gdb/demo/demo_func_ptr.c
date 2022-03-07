#include <stdio.h>
#include <unistd.h>

int main(int argc, char const **argv)
{
	printf("main function...\n");
	sleep(2);

	int (*main_ptr)(int argc, char const **argv) = main;
	main_ptr(argc, argv);

	return 0;
}
