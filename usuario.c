#include <stdio.h>
#include "Lista.h"

int main() {
	struct Lista *ordenada, *desordenada;

	ordenada = criar(20);
	desordenada = criar(10);
		
	int numero;
	do {
		printf("Digite um valor para a lista ordenada (0 para encerrar): ");
		scanf("%d", &numero);

		if (numero != 0) {
			adicionar(ordenada, numero, ORDEM);
			adicionar(desordenada, numero, INICIO);

			imprimir(ordenada);
			imprimir(desordenada);
		}
	}
	while (numero != 0);

	printf("Digite um numero para remover das listas: ");
	scanf("%d", &numero);

	remover(ordenada, numero);
	remover(desordenada, numero);

	imprimir(ordenada);
	imprimir(desordenada);

	ordenar(desordenada);
	imprimir(desordenada);

	destruir(ordenada);
	destruir(desordenada);

	return 0;
}

