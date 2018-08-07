#include <stdio.h>
#include "ListaE.h"

int main() {
	struct Lista *ordenada, *desordenada;

	ordenada = criar();
	desordenada = criar();
		
	int numero;
	do {
		printf("Digite um valor para a lista ordenada (0 para encerrar): ");
		scanf("%d", &numero);

		if (numero != 0) {
			adicionar(ordenada, numero, ORDEM);
			
			if (numero % 2 == 0) {
				adicionar(desordenada, numero, INICIO);
			}
			else {
				adicionar(desordenada, numero, FIM);
			}

			imprimir(ordenada);
			imprimir(desordenada);
		}
	}
	while (numero != 0);

	printf("Digite um numero para remover das listas: ");
	scanf("%d", &numero);

	remover_val(ordenada, numero);
	remover_val(desordenada, numero);

	imprimir(ordenada);
	imprimir(desordenada);
	
	printf("Digite uma posicao para remover das listas: ");
	scanf("%d", &numero);
	
	int valor;
	remover_npos(ordenada, numero, &valor);
	printf("Removi o valor %d da lista ordenada.\n", valor);
	remover_npos(desordenada, numero, &valor);
	printf("Removi o valor %d da lista desordenada.\n", valor);

	imprimir(ordenada);
	imprimir(desordenada);
	
	destruir(ordenada);
	destruir(desordenada);

	return 0;
}

