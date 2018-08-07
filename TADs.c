#include <stdlib.h>
#include <stdio.h>
#include "TADs.h"

/******************************************
 * TAD "Pilha"
 *****************************************/

struct Pilha {
	char* vetor;
	size_t max;
	int topo;
};

struct Pilha* p_criar(size_t max) {
	struct Pilha* p = (struct Pilha*) malloc(sizeof(struct Pilha));
	p->vetor = (char*) malloc(sizeof(char) * max);
	p->max = max;
	p->topo = -1;	// pilha vazia!
	return p;
}

void p_destruir(struct Pilha* p) {
	free(p->vetor);
	free(p);
}

bool push(struct Pilha* p, char c) {
	if (p_overflow(p)) {
		return false;
	}
	p->vetor[++p->topo] = c;
	return true;
}

char pop(struct Pilha* p) {
	if (p_underflow(p)) {
		return EOF;
	}
	char c = p->vetor[p->topo--];
	return c;
}

bool p_underflow(struct Pilha* p) {
	return p->topo == -1;
}

bool p_overflow(struct Pilha* p) {
	return p->topo == p->max-1;
}

void p_imprimir(struct Pilha* p) {
	if (p_underflow(p)) {
		puts("(vazio)");
		return;
	}
	int i;
	for (i=0; i<=p->topo; ++i) {
		printf("%c ", p->vetor[i]);
	}
	puts("(topo)");
}

/******************************************
 * TAD "Fila" (circular)
 *****************************************/

struct Fila {
	char* vetor;
	size_t max;
	int inicio, fim;
};

struct Fila* f_criar(size_t max) {
	struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
	f->max = max+1;	// a fila circular "sacrifica" uma posicao!
	f->vetor = (char*) malloc(sizeof(char) * f->max);
	f->inicio = f->fim = f->max-1;
	return f;
}

void f_destruir(struct Fila* f) {
	free(f->vetor);
	free(f);
}

bool enqueue(struct Fila* f, char c) {
	if (f_overflow(f)) {
		return false;
	}
	f->fim = f->fim == f->max-1? 0: f->fim+1;
	f->vetor[f->fim] = c;
	return true;
}

char dequeue(struct Fila* f) {
	if (f_underflow(f)) {
		return EOF;
	}
	f->inicio = f->inicio == f->max-1? 0: f->inicio+1;
	char c = f->vetor[f->inicio];
	return c;
}

bool f_underflow(struct Fila* f) {
	return f->inicio == f->fim;
}

bool f_overflow(struct Fila* f) {
	return f->fim == (f->inicio == 0? f->max-1: f->inicio-1);
}

void f_imprimir(struct Fila* f) {
	if (f_underflow(f)) {
		puts("(vazio)");
		return;
	}
	printf("(inicio) ");
	int j = f->inicio;
	do {
		j = j == f->max-1? 0: j+1;
		printf("%c ", f->vetor[j]);
	}
	while (j != f->fim); 
	puts("(fim)");
}

