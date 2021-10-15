#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mirror(char *s)
{
	/* TODO */
	s[0] = '0';
}

int main()
{
	/* TODO: Test function */
	// Sirurile "AnaAreMere" sunt plasate intr-o zona de date READ-ONLY
	// ASA NU
	// char *str1 = "AnaAreMere";
	// mirror(str1);

	// ASA NU
	// mirror("AnaAreMere");

	// Sirurile de mai jos sunt puse pe stiva (READ-WRITE)
	char str2[] = "AnaAreMere";
	char str3[11] = "AnaAreMere";
	
	mirror(str2);
	// printf("str2 = %s\n", str2);

	mirror(str3);
	// printf("str3 = %s\n", str3);

	return 0;
}

