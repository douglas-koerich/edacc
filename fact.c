#include <stdlib.h>
#include <stdio.h>

unsigned fatorial(unsigned);

int main(void) {
	unsigned num;
	printf("Digite um numero: ");
	scanf("%u", &num);

	unsigned fact = fatorial(num);

	printf("O fatorial de %u eh %u\n", num, fact);

	return EXIT_SUCCESS;
}

/* Formula do fatorial: n! = 1.2.3...(n-2)(n-1)n */
/* Para resolver o fatorial, podemos usar uma forma iterativa (laco) */

/*
unsigned fatorial(unsigned n) {
	unsigned f = 1; // acumulador do produtorio
	unsigned i;     // varia de 1 a n
	for (i = 1; i <= n; ++i) {
		f *= i;
	}
	return f;
}
*/

/* A formula acima pode ser vista da seguinte maneira:
   n! = (n-1)!.n
   Por definicao: 0! = 1 <-- "condicao terminal da recursivade"
   */
unsigned fatorial(unsigned n) {
	if (n == 0) {
		return 1; // condicao terminal
	}
	if (n == 1) {
		return n; // outra condicao terminal
	}
	unsigned f = n * fatorial(n - 1);
	return f;
}