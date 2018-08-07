#include <stdio.h>
#include "exerc1lista.h"

int main() {
	int vetor1[] = { 2, 3, 5, 7, 11, 13, 17, -1 },
		vetor2[] = { 2, 3, 5, 8, 13, 21, 34, -1 },
		i = 0;
	struct Lista* lista1 = cria(),
			    * lista2 = cria();
	imprime(lista1);
	imprime(lista2);

	while (vetor1[i] > 0) {
		if (i % 2 == 0) {
			insereInicio(lista1, vetor1[i]);
		}
		else {
			insereFim(lista1, vetor1[i]);
		}
		++i;
	}
	imprime(lista1);

	i = 0;
	while (vetor2[i] > 0) {
		if (i % 2 == 0) {
			insereInicio(lista2, vetor2[i]);
		}
		else {
			insereFim(lista2, vetor2[i]);
		}
		++i;
	}
	imprime(lista2);

	lista1 = concatena(lista1, lista2);

	imprime(lista1);

	destroi(lista1);
	return 0;
}

