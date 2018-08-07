#include <stdio.h>
#include "lcirc.h"
#include "exerc5.h"

int main() {
	int v1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1 };
	int v2[] = { 1, 13, 5, 7, 3, 19, 11, -1 };
	int i, temp;

	Lista lista, lista_ordenada;

	// Vamos preencher listas circulares
	inicia(&lista);
	inicia(&lista_ordenada);

	for (i=0; v1[i] >= 0; ++i) {
		if (i % 2) 	insInicio(&lista, v1[i]);
		else		insFim(&lista, v1[i]);
	}
	for (i=0; v2[i] >= 0; ++i) {
		insValor(&lista_ordenada, v2[i]);
	}
	printf("Lista circular nao-ordenada inicial: ");
	imprime(&lista);
	printf("Lista circular ordenada inicial: ");
	imprime(&lista_ordenada);

	// Exercicio 6: Adiciona um novo item a lista
	insValor(&lista_ordenada, 4);
	insValor(&lista_ordenada, 40);
	printf("Lista circular ordenada depois das insercoes: ");
	imprime(&lista_ordenada);

	// Antes de proceder ah inversao da lista, vamos testar
	// a remocao de alguns nos
	remValor(&lista, 4);
	printf("Removeu 4 da lista: ");
	imprime(&lista);

	remInicio(&lista, &temp);
	printf("Removeu %d do inicio: ", temp);
	imprime(&lista);

	remFim(&lista, &temp);
	printf("Removeu %d do fim: ", temp);
	imprime(&lista);

	// Exercicio 5: Inverte a lista
	inverte(&lista);
	printf("Lista invertida: ");
	imprime(&lista);

	inverte(&lista_ordenada);
	printf("Lista ordenada invertida: ");
	imprime(&lista_ordenada);

	finaliza(&lista);
	finaliza(&lista_ordenada);

	return 0;
}

