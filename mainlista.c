#include <stdio.h>
#include "lsimples.h"

int main() {
	int vetor[] = { 1, 2, 3, 5, 7, -1 },
		i = 0;
	struct Lista* lista = cria();
	imprime(lista);

	while (vetor[i] > 0) {
		if (i % 2 == 0) {
			insereInicio(lista, vetor[i]);
		}
		else {
			insereFim(lista, vetor[i]);
		}
		imprime(lista);
		++i;
	}

	i = 0;
	while (!underflow(lista)) {
		int nada;
		if (i % 2 == 0) {
			removeInicio(lista, &nada);
		}
		else {
			removeFim(lista, &nada);
		}
		imprime(lista);
		++i;
	}
	destroi(lista);
	return 0;
}

