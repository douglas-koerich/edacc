#include <stdlib.h>
#include <stdio.h>
#include "Pilha.h"

struct Pilha {
	char* vetor;
	size_t max;
	int topo;
};

struct Pilha* criar(size_t max) {
	struct Pilha* p = (struct Pilha*) malloc(sizeof(struct Pilha));
	p->vetor = (char*) malloc(sizeof(char) * max);
	p->max = max;
	p->topo = -1;	// pilha vazia!
	return p;
}

void destruir(struct Pilha* p) {
	free(p->vetor);
	free(p);
}

bool push(struct Pilha* p, char c) {
	if (overflow(p)) {
		return false;
	}
	p->vetor[++p->topo] = c;
	return true;
}

char pop(struct Pilha* p) {
	if (underflow(p)) {
		return EOF;
	}
	char c = p->vetor[p->topo--];
	return c;
}

bool underflow(struct Pilha* p) {
	return p->topo == -1;
}

bool overflow(struct Pilha* p) {
	return p->topo == p->max-1;
}

