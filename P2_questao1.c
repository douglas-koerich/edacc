#include <stdio.h>

float soma(int);

int main(void) {
	int n;
	printf("Digite o valor de n: ");
	scanf("%d", &n);

	float S = soma(n);
	printf("A soma da serie para n=%d eh S=%.2f.\n", n, S);
	return 0;
}

/*
 * S(n) = (n^2 + 1) / (n + 3) + S(n-1), se n >= 1
 * S(n) = 0, se n = 0
 */

float soma(int n) {
	if (n == 0) {	// condicao terminal
		return 0;	// retorno sem chamada recursiva
	}
	float S = (n*n + 1.0)/(n + 3.0);	// termo de n
	S += soma(n-1);	// soma com o retorno da chamada recursiva
	return S;
}

