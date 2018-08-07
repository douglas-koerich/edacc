#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerc5lista.h"

void inicia(Lista* l) {
	l->tamanho = 0;
	l->cabeca = l->cauda = NULL;
}

void finaliza(Lista* l) {
	while (l->cabeca != NULL) {
		Noh* x = l->cabeca;
		l->cabeca = x->proximo;
		free(x);
	}
	l->cauda = NULL;
	l->tamanho = 0;
}

void insere(Lista* l, int num) {
	Noh* n = (Noh*) malloc(sizeof(Noh));
	n->numero = num;
	n->anterior = NULL;
	n->proximo = l->cabeca;

	++l->tamanho;
	if (l->cabeca != NULL) {
		l->cabeca->anterior = n;
	}
	l->cabeca = n;
	if (l->cauda == NULL) {
		l->cauda = n;
	}
}

void ordena(Lista* l) {
	unsigned t;
	bool troca;
	for (t=1, troca=true; t<=l->tamanho && troca; ++t) {
		troca = false;
		Noh* x = l->cauda;
		while (x->anterior != NULL) {
			if (x->numero < x->anterior->numero) {
				int aux = x->numero;
				x->numero = x->anterior->numero;
				x->anterior->numero = aux;
				troca = true;
			}
			x = x->anterior;
		}
		x = l->cabeca;
		while (x->proximo != NULL) {
			if (x->numero > x->proximo->numero) {
				int aux = x->numero;
				x->numero = x->proximo->numero;
				x->proximo->numero = aux;
				troca = true;
			}
			x = x->proximo;
		}
	}
}

void imprime(Lista* l) {
	Noh* x = l->cabeca;
	while (x != NULL) {
		printf("%d ", x->numero);
		x = x->proximo;
	}
}

int main() {
	size_t tam;
	printf("Qual o tamanho da lista a preencher? ");
	scanf("%u", &tam);

	Lista lista;
	inicia(&lista);

	int i;
	for (i=0; i<tam; ++i) {
		int num = rand() % 1000 + 1;
		insere(&lista, num);
	}
	printf("Lista na ordem original: ");
	imprime(&lista);
	putchar('\n');

	ordena(&lista);

	printf("Lista ordenada: ");
	imprime(&lista);
	putchar('\n');

	finaliza(&lista);

	return 0;
}
