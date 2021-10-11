#include <stdio.h>

int main(int argc, char const *argv[])
{
	int cond = 1, cond1 = 1;
	goto ceva;

	// cod -> nu se executa
	printf("Nu se executa");

ceva:
	printf("Se executa\n");

	// if cu goto
	if (cond) {
		// ceva
	} else {
		// altceva
	}

	if (!cond)
		goto else_body;

	// ceva

	goto after_else;

else_body:
	// altceva

after_else:

// 	for (ceva) {
// 		for (alteceva) {
// 			for (blabla) {
// 				if (caca)
// 					goto exit_loops;
// 			}
// 		}
// 	}
// exit_loops:

	// while cu goto
	while (cond) {
		// ceva
	}

whie_body:
	if (!cond)
		goto exit_while;

	// ceva
	goto whie_body;

exit_while:

	// orice

	// NU ASA. Folositi de Morgan
	if (cond1 && cond)
		goto exit;
	if (cond1 || cond)
		goto exit;

	// ex. de Morgan:
	!(cond && cond1) == !cond || !cond1;
	if (!cond1)
		goto exit;
	if (!cond)
		goto exit;

exit:
	return 0;
}
