#include <stdlib.h>
#include <stdio.h>
#include "ldupla.h"

struct Noh {
	int elemento;
	struct Noh* proximo;
	struct Noh* anterior;
};

struct Lista {
	struct Noh* cabeca;
};

struct Lista* cria(void) {
	struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
	l->cabeca = NULL;
}

void destroi(struct Lista* l) {
	while (l->cabeca != NULL) {
		struct Noh* cabeca = l->cabeca;
		l->cabeca = cabeca->proximo;
		free(cabeca);
	}
}

void imprime(struct Lista* l) {
	printf("||");
	struct Noh* c = l->cabeca;
	while (c != NULL) {
		printf("(<-%p-[%d]-%p->)", c->anterior, c->elemento, c->proximo);
		c = c->proximo;
	}
	printf("||\n");
}

bool insFim(struct Lista* l, int x) {
	struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
	p->elemento = x;
	p->proximo = NULL;
	if (l->cabeca == NULL) {
		p->anterior = NULL;
		l->cabeca = p;
		return true;
	}
	struct Noh* c = l->cabeca;
	while (c->proximo != NULL) {
		c = c->proximo;
	}
	p->anterior = c;
	c->proximo = p;
	return true;
}

bool insAntes(struct Lista* l, int x, int n) {
	struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
	p->elemento = x;
	if (n == 1) {
		p->proximo = l->cabeca;
		p->anterior = NULL;
		l->cabeca = p;
		if (p->proximo != NULL) {
			p->proximo->anterior = p;
		}
		return true;
	}
	struct Noh* c = l->cabeca;
	int contador = 1;
	while (contador < n && c->proximo != NULL) {
		++contador;
		c = c->proximo;
	}
	if (contador == n) {
		p->anterior = c->anterior;
		p->proximo = c;
		p->anterior->proximo = c->anterior = p;
	}
	else {
		p->anterior = c;
		p->proximo = NULL;
		c->proximo = p;
	}
	return true;
}

bool insDepois(struct Lista* l, int x, int n) {
	struct Noh* p = (struct Noh*) malloc(sizeof(struct Noh));
	p->elemento = x;
	if (l->cabeca == NULL) {
		p->anterior = p->proximo = NULL;
		l->cabeca = p;
		return true;
	}
	struct Noh* c = l->cabeca;
	int contador = 1;
	while (contador < n && c->proximo != NULL) {
		++contador;
		c = c->proximo;
	}
	p->anterior = c;
	p->proximo = c->proximo;
	c->proximo = p;
	if (p->proximo != NULL) {
		p->proximo->anterior = p;
	}
	return true;
}

