#include <stdio.h>
#include "ldupla.h"

int main() {
	int i = 0, vetor[] = { 1, 2, 3, 4, 5, -1 };
	struct Lista* l = cria();

	while (vetor[i] >= 0) {
		insFim(l, vetor[i++]);
	}
	imprime(l);

	int x;
	printf("Digite o valor a inserir: ");
	scanf("%d", &x);
	int n;
	printf("Digite a posicao de referencia: ");
	scanf("%d", &n);
	int pos;
	do {
		printf("Digite 1 para antes, 2 para depois: ");
		scanf("%d", &pos);
	} while (pos != 1 && pos != 2);

	if (pos == 1) {
		insAntes(l, x, n);
	}
	else {
		insDepois(l, x, n);
	}
	imprime(l);

	destroi(l);
	return 0;
}
