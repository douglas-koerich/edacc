#include <stdio.h>
#include <stdlib.h>
#include "algbusca.h"

int main(int argc, char* argv[]) {
	if (argc < 3) {
		puts("Numero invalido de parametros");
		printf("Use: %s <num-elementos> <algoritmo>\n", argv[0]);
		puts("     onde algoritmo eh busca:");
		puts("       1: sequencial.");
		puts("       2: binaria.");
		puts("       3: interpolacao.");
		return -1;
	}
	int i, tam = atoi(argv[1]);
	int* vetor = (int*) malloc(tam*sizeof(int));
	for (i=0; i<tam; ++i) {
		vetor[i] = i;
	}
	switch (atoi(argv[2])) {
		case 1: buscaSequencial(vetor, tam, i);	// i tem um a mais que o ultimo valor
				break;

		case 2: buscaBinaria(vetor, 0, tam-1, i);
				break;

		case 3: buscaInterpolacao(vetor, 0, tam-1, i);
				break;

		default:
			puts("Codigo de algoritmo invalido");
	}
	free(vetor);
	return 0;
}

