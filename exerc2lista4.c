#include <stdio.h>

float media_r(int*, int);

int main() {
	int n;

	printf("Digite o numero de elementos do vetor: ");
	scanf("%d", &n);

	int vetor[n];
	int i;
	for (i=0; i<n; ++i) {
		vetor[i] = i+1;
	}

	printf("Vetor gerado: ");
	for (i=0; i<n; ++i) {
		printf("%d ", vetor[i]);
	}
	putchar('\n');

	float media = media_r(vetor, n);

	printf("A media dos valores armazenados no vetor eh %f\n", media);
	return 0;
}

float media_r(int* vetor, int n) {
	if (n == 0) {       /* 3T */
		return 0.0;     /* 2T */
	}
	if (n == 1) {       /* 3T */
		return *vetor;  /* 3T */
	}
    // Media ponderada: o peso do elemento da vez eh 1 (um elemento) frente
    // ao peso 'n-1' (dos n-1 elementos restantes)
    // (A media aritmetica eh um caso particular da media ponderada onde todos
    // os elementos tem peso 1 e a soma dos pesos - unitarios! - eh o numero
    // de elementos do conjunto)
	float m = ((1 * *vetor) + ((n-1) * media_r(vetor+1, n-1)))/n;   /* 20T + FC(n-1) */
	return m;           /* 2T */
}

/* Para T = 1:
 * FC(n) = FC(n-1) + 28, se n > 1
 *       = 9           , se n = 1
 *
 * Desenvolvendo/expandindo:
 * FC(n) = FC(n-2) + 28 + 28 ...
 * ...
 * FC(n) = FC(n-i) + 28i
 *
 * Fazendo n-i = 1 para obtermos FC(1), temos i = n-1. Assim,
 * FC(n) = FC(1) + 28(n-1)
 *       = 9 + 28n - 28
 *
 * O que finalmente nos dah
 * FC(n) = 28n - 19
 * Complexidade: O(n)
 */

