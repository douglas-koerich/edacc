#include <stdio.h>
#include "exerc4pilha.h"

struct Pilha {
	int* vetor;
	size_t max;
	int topo;
};

struct Pilha* cria(size_t tamanho) {
	struct Pilha* pilha = (struct Pilha*) malloc(sizeof(struct Pilha));
	pilha->vetor = (int*) malloc(sizeof(int) * tamanho);
	pilha->max = tamanho;
	pilha->topo = -1;
	return pilha;
}

void destroi(struct Pilha* pilha) {
	free(pilha->vetor);
	free(pilha);
}

bool underflow(const struct Pilha* pilha) {
	return pilha->topo == -1;
}

bool overflow(const struct Pilha* pilha) {
	return pilha->topo == pilha->max - 1;
}

bool push(struct Pilha* pilha, int valor) {
	if (overflow(pilha)) {
		return false;
	}
	pilha->vetor[++pilha->topo] = valor;
	return true;
}

bool pop(struct Pilha* pilha, int* endereco) {
	if (underflow(pilha)) {
		return false;
	}
	if (endereco == NULL) {	// robustez da biblioteca
		return false;
	}
	*endereco = pilha->vetor[pilha->topo--];
	return true;
}

void print(const struct Pilha* pilha) {
	printf("\nBase--| ");
	int i = 0;
	while (i <= pilha->topo) {
		printf("%d ", pilha->vetor[i]);
		++i;
	}
	printf("|--Topo\n");
}
