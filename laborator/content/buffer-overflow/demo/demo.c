#include <stdio.h>
#include <stdlib.h>

void manele(int x)
{
	printf("GGWP!\n");

	if (x == 0xDEADC0DE)
		printf("OMG!\n");  // TODO for you
}

void read_data()
{
	unsigned int x = 2;
	char s[10];

	scanf("%s", s);

	if (x == 0xCAFEBABE)
		printf("So far, so good!\n");
}

int main(void)
{
	read_data();
	return 0;
}
