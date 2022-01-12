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
	// "manele" se stocheaza intr-o zona de date READ-ONLY
	// ASA NU
	mirror("manele");

	char *s = "manele";
	mirror(s);

	// s1 si s2 se stocheaza pe stiva: READ-WRITE
	// ASA DA
	char s1[] = "manele";
	char s2[7] = "manele";

	mirror(s1);
	mirror(s2);

	// s3 se stocheza pe heap: READ-WRITE
	// e ok sizeof-ul asta. sizeof se evalueaza la compilare => nu se aloca nimic pt "manele"
	// sizeof("manele") == 7; contine si \0
	// ASA DA (dar nu-i eficient sa aloci si memorie pe heap pt ceva ce poate fi tinut pe stiva)
	char *s3 = malloc(sizeof("manele"));
	strcpy(s3, "manele");
	mirror(s3);

	return 0;
}

