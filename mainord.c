#include <stdlib.h>	// rand()
#include <stdio.h>	// printf()/scanf()/...
#include <time.h>	// time()
#include "registro.h"	// contem a definicao dos registros a serem criados e
						// ordenados pelos diferentes algoritmos
#include "algord.h"	// bubblesort()/...

#define NUM_REGISTROS 17	// tamanho do nosso "banco de dados" (vetor de registros)

int main() {
	// O banco de dados do programa (tabela de registros em memoria)
	Registro banco_de_dados[NUM_REGISTROS];

	// Preenche o vetor com chaves aleatorias e outros campos vazios
	srand((unsigned) time(0));	// inicializa algoritmo randomico
	int r;
	for (r=0; r<NUM_REGISTROS; ++r) {
		banco_de_dados[r].chave = rand() % 1000;	// limita chave entre 0 e 999
		banco_de_dados[r].descricao[0] = '\0';		// string vazia (soh ilustracao)
		banco_de_dados[r].valor = 0.0;				// valor nulo (idem)
	}

	// Imprime a sequencia original de chaves
	puts("Banco de dados em sequencia original");
	for (r=0; r<NUM_REGISTROS; ++r) {
		printf("%d ", banco_de_dados[r].chave);
	}
	putchar('\n');

	// Ordenando o banco de dados
	// bubblesort(banco_de_dados, NUM_REGISTROS);
	// selectsort(banco_de_dados, NUM_REGISTROS);
	// insertsort(banco_de_dados, NUM_REGISTROS);
	// shellsort(banco_de_dados, NUM_REGISTROS);
	// mergesort(banco_de_dados, 0, NUM_REGISTROS-1);
	quicksort(banco_de_dados, 0, NUM_REGISTROS-1);

	// Imprime a sequencia ordenada de chaves
	puts("Banco de dados em sequencia ordenada");
	for (r=0; r<NUM_REGISTROS; ++r) {
		printf("%d ", banco_de_dados[r].chave);
	}
	putchar('\n');

	return 0;
}

