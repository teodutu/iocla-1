#include <stdio.h>
#include <stdlib.h>

void manele(int param)
{
	printf("GGWP!\n");

	if (param == 0xDEADC0DE)
		printf("OMG!\n");  /* TODO for you */
}

void read_data()
{
	char s[10];
	unsigned int val = 2;

	/**
	 * The same vulnerability occurs when using:
	 *     gets(s);
	 *     fgets(s, 32, stdin);
	 */
	scanf("%s", s);

	printf("val = 0x%X\n", val);

	if (val == 0xCAFEBABE)
		printf("So far, so good!\n");
}

int main(void)
{
	read_data();
	return 0;
}
