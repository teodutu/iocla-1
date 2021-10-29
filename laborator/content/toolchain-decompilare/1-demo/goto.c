#include <stdio.h>

int main(void)
{
	int cond1 = 1, cond2 = 1;

	goto ceva;

	printf("Nu se executa\n");

ceva:
	printf("Se executa\n");

/*------------------------------------------*/
	// if cu goto
	if (cond1)
		printf("if body\n");
	else
		printf("else body\n");
	// <=>
	if (!cond1)
		goto else_body;
	printf("if body\n");

	goto exit_if;

else_body:
	printf("else body\n");

exit_if:

/*------------------------------------------*/
	cond1 = 2;
	
	// while cu goto
	while (cond1) {
		printf("while body\n");
		--cond1;
	}
	// <=>
	cond1 = 2;
while_body:
	if (!cond1)
		goto exit_while;

	printf("while body\n");
	--cond1;

	goto while_body;

exit_while:

/*------------------------------------------*/
	cond1 = 1;
	// ASA NU
	if (cond1 && cond2)
		printf("cond1 && cond2\n");

	// ASA DA
	// folosim de Morgan
	// !(cond1 && cond2) == !cond! || !cond2
	if (!cond1)
		goto exit;
	if (!cond2)
		goto exit;

	printf("cond1 && cond2\n");

exit:
	return 0;
}
