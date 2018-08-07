#include <stdio.h>
#include "lsimples.h"

int main() {
	struct Lista* lista = cria();
	imprime(lista);
	int num;
	do {
		printf("Digite um valor (0 para interromper): ");
		scanf("%d", &num);
		insereOrdem(lista, num);
		imprime(lista);
	} while (num != 0);

	printf("Digite um valor para remover da lista: ");
	scanf("%d", &num);
	removeValor(lista, num);
	imprime(lista);

	destroi(lista);
	return 0;
}

