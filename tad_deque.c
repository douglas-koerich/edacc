#include <stdio.h>
#include "tad_deque.h"

struct Deque {
	int* vetor;
	size_t max;
	int inicio, fim;
};

struct Deque* cria(size_t tamanho) {
	struct Deque* d = (struct Deque*) malloc(sizeof(struct Deque));
	d->vetor = (int*) malloc((tamanho+1)*sizeof(int));
	d->max = tamanho+1;
	d->fim = d->max-1;
	d->inicio = d->max-1;
	return d;
}

void destroi(struct Deque* d) {
	free(d->vetor);
	free(d);
}

bool underflow(const struct Deque* d) {
	return d->inicio == d->fim;
}

bool overflow(const struct Deque* d) {
	return d->inicio == 0? (d->fim == d->max-1) : (d->fim == d->inicio - 1);
}

bool inserir(struct Deque* d, enum Lado l, int novo) {
	if (overflow(d)) {
		return false;
	}
	if (l == INICIO) {
		// O indice inicio estah na posicao VAZIA anterior ao primeiro elemento
		// do deque; insere nessa posicao e decrementa o valor do indice
		d->vetor[d->inicio] = novo;
		if (d->inicio == 0) {
			d->inicio = d->max-1;
		}
		else {
			--d->inicio;
		}
	}
	else {
		// Como na fila...
		if (d->fim == d->max-1) {
			d->fim = 0;
		}
		else {
			++d->fim;
		}
		d->vetor[d->fim] = novo;
	}
	return true;
}

bool remover(struct Deque* d, enum Lado l, int* endereco) {
	if (underflow(d)) {
		return false;
	}
	if (l == INICIO) {
		// Como na fila...
		if (d->inicio == d->max-1) {
			d->inicio = 0;
		}
		else {
			++d->inicio;
		}
		*endereco = d->vetor[d->inicio];
	}
	else {
		*endereco = d->vetor[d->fim];
		if (d->fim == 0) {
			d->fim = d->max-1;
		}
		else {
			--d->fim;
		}
	}
	return true;
}

void print(const struct Deque* d) {
	printf("Inicio--| ");
	int i;
	int contador = 0;
	i = d->inicio;
	while (i != d->fim) {
		if (i == d->max-1) i = 0;
		else ++i;
		printf("%d@%d ", d->vetor[i], i);
		++contador;
	}
	printf("|--Fim\n");
	printf("Existem %d posicoes livres no vetor\n",
		   d->max - 1 - contador);
}

