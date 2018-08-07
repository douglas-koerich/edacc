#include <stdlib.h>
#include <string.h>
#include "filareg.h"

struct No {
	R elemento;
	struct No* proximo;
	struct No* anterior;
};
typedef struct No No;

struct Fila {
	No* inicio;
	No* fim;
};

struct Fila* criar(void) {
	struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
	f->inicio = f->fim = NULL;
	return f;
}

void destruir(struct Fila* f) {
	while (f->inicio != NULL) {
		No* p = f->inicio;
		f->inicio = p->proximo;
		free(p);
	}
	free(f);
}

bool underflow(struct Fila* f) {
	return f->inicio == NULL;
}

bool enqueue(struct Fila* f, const R* reg) {
	No* p = (No*) malloc(sizeof(No));
	p->proximo = NULL;
	p->anterior = f->fim;
	memcpy(&p->elemento, reg, sizeof(R));
	if (f->fim != NULL) {
		(f->fim)->proximo = p;
	}
	if (f->inicio == NULL) {
		f->inicio = p;
	}
	f->fim = p;
	return true;
}

bool dequeue(struct Fila* f, R* reg) {
	if (underflow(f)) {
		return false;
	}
	No* p = f->inicio;
	f->inicio = p->proximo;
	if (f->inicio != NULL) {
		f->inicio->anterior = NULL;
	}
	else {
		f->fim = NULL;
	}
	memcpy(reg, &p->elemento, sizeof(R));
	free(p);
	return true;
}

