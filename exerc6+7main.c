#include <stdio.h>
#include <stdlib.h>
#include "exerc6+7hashing.h"

int main(void) {
	int vetor[] = { 1000, 1050, 1075, 1100, 1300, 1350, 1400, 1440, 1480,
					1600, 1700, 1800, 1850, 1900, 1950, 1975, 2000, 2200,
					2400, 2430, 2450, 2500, 2600, 2700, 2950, 3100, 3150,
					-1 };
	int i = 0, pos;
	TabelaHashing tabela = criar();

	while (vetor[i] > 0) {
		pos = inserir(tabela, vetor[i]);
		printf("h(%d) = %d, inseriu em %d.\n", vetor[i], h(vetor[i]), pos);
		++i;
	}
	pos = remover(tabela, 1800);
	if (pos >= 0) {
		printf("Removeu da posicao %d.\n", pos);
	}
	else {
		puts("Nao encontrou chave = 1800.");
	}
	pos = remover(tabela, 1500);
	if (pos >= 0) {
		puts("Isto nao deveria acontecer!...");
	}
	else {
		puts("Nao encontrou chave = 1500.");
	}
	destruir(tabela);

	return EXIT_SUCCESS;
}

