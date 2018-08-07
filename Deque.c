#include <stdlib.h>
#include <stdio.h>
#include "Deque.h"

struct Deque {
	char* vetor;
	size_t max, contador;
	int inicio, fim;
};

struct Deque* criar(size_t max) {
	struct Deque* d = (struct Deque*) malloc(sizeof(struct Deque));
	d->vetor = (char*) malloc(sizeof(char) * max);
	d->max = max;
	d->contador = 0;	// deque vazio!
	d->inicio = 0;
	d->fim = max-1;
	return d;
}

void destruir(struct Deque* d) {
	free(d->vetor);
	free(d);
}

bool add(struct Deque* d, enum Lado l, char c) {
	if (overflow(d)) {
		return false;
	}
	++d->contador;
	if (l == FIM) {
		d->fim = d->fim==d->max-1? 0: d->fim+1;
		d->vetor[d->fim] = c;
	}
	else {
		d->inicio = d->inicio==0? d->max-1: d->inicio-1;
		d->vetor[d->inicio] = c;
	}
	return true;
}

char del(struct Deque* d, enum Lado l) {
	if (underflow(d)) {
		return EOF;
	}
	--d->contador;
	char c;
	if (l == INICIO) {
		c = d->vetor[d->inicio];
		d->inicio = d->inicio==d->max-1? 0: d->inicio+1;
	}
	else {
		c = d->vetor[d->fim];
		d->fim = d->fim==0? d->max-1: d->fim-1;
	}	
	return c;
}

bool underflow(struct Deque* d) {
	return d->contador == 0;
}

bool overflow(struct Deque* d) {
	return d->contador == d->max;
}

void imprimir(struct Deque* d) {
	if (underflow(d)) {
		puts("(vazio)");
		return;
	}
	printf("(inicio) ");
	int j = d->inicio;
	size_t n;
	for (n=1; n<=d->contador; ++n) {
		printf("%c ", d->vetor[j]);
		j = j == d->max-1? 0: j+1;
	}
	puts("(fim)");
}

