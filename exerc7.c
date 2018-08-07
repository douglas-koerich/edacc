#include <stdio.h>
#include <stdlib.h>
#include "exerc7.h"

void inicia(Lista* l) {
	l->contador = 0;
	l->cabeca = l->cauda = NULL;
}

void finaliza(Lista* l) {
	while (l->contador > 0) {
		int temp;
		remInicio(l, &temp);
	}
}

bool underflow(Lista* l) {
	return l->contador == 0;
}

void insFim(Lista* l, int novo) {
	NoLista* n = (NoLista*) malloc(sizeof(NoLista));
	n->numero = novo;
	n->proximo = NULL;
	++l->contador;
	if (l->cauda != NULL) {
		l->cauda->proximo = n;
	}
	if (l->cabeca == NULL) {
		l->cabeca = n;
	}
	l->cauda = n;
}

bool remInicio(Lista* l, int* removido) {
	if (underflow(l)) {
		return false;
	}
	NoLista* x = l->cabeca;
	l->cabeca = x->proximo;
	if (l->cauda == x) {
		l->cauda = NULL;
	}
	--l->contador;
	*removido = x->numero;
	free(x);
	return true;
}

void imprime(Lista* l) {
	NoLista* x = l->cabeca;
	while (x != NULL) {
		printf("%d ", x->numero);
		x = x->proximo;
	}
	putchar('\n');
}

Lista* intercala(Lista* l1, Lista* l2) {
	Lista* nova = (Lista*) malloc(sizeof(Lista));	// aloca no-cabecalho
	inicia(nova);

	while (!underflow(l1) || !underflow(l2)) {
		if (underflow(l1)) {	// l1 ja ficou vazia, mas l2 ainda nao
			while (!underflow(l2)) {
				int temp;
				remInicio(l2, &temp);
				insFim(nova, temp);
			}
			continue;
		}
		if (underflow(l2)) {	// l1 ja ficou vazia, mas l2 ainda nao
			while (!underflow(l1)) {
				int temp;
				remInicio(l1, &temp);
				insFim(nova, temp);
			}
			continue;
		}
		int temp;
		remInicio(l1, &temp);
		insFim(nova, temp);
		remInicio(l2, &temp);
		insFim(nova, temp);
	}
	return nova;
}

#include <time.h>

int main() {
	srand((unsigned) time(0));

	Lista lista1, lista2;

	inicia(&lista1);
	inicia(&lista2);

	int i;
	for (i=0; i<10; ++i) {
		insFim(&lista1, rand() % 1000);
	}
	for (i=0; i<5; ++i) {
		insFim(&lista2, rand() % 1000);
	}
	printf("Lista 1: "); imprime(&lista1);
	printf("Lista 2: "); imprime(&lista2);

	Lista* inter = intercala(&lista1, &lista2);

	printf("Lista inter: "); imprime(inter);
	finaliza(inter);

	free(inter);

	return 0;
}

