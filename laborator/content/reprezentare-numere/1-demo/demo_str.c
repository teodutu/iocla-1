#include <stdio.h>

int main(int argc, char const *argv[])
{
	// char *s = "asdf";  // "asdf" e read-only
	char s[] = "asdf";  // "asdf" e read-write

	char *p;

	for (p = s; *p != '\0'; ++p) {
		*p = 'n';
		printf("%p -> %c\n", p, *p);
	}

	return 0;
}
