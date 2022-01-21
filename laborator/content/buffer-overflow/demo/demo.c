#include <stdio.h>
#include <stdlib.h>

void manele(int param)
{
	printf("GGWP!\n");

	if (param == 0xDEADC0DE)
		printf("OMG!\n");  // TODO for you
}

void read_data()
{
	unsigned int val = 2;
	char s[10];

	scanf("%s", s);
	// gets(s);
	// fgets(s, 32, stidn);

	if (val == 0xCAFEBABE)
		printf("So far, so good!\n");
}

int main(void)
{
	read_data();
	return 0;
}
