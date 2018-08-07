#include <stdlib.h>
#include <stdio.h>
#include "exerc5.h"

void l_inicia(Lista* l) {
	*l = NULL;
}

void l_finaliza(Lista* l) {
	if (l_underflow(l)) {
		return;
	}
	NoLista* ultimo = *l;
	do {
		NoLista* x = *l;
		*l = x->proximo;
		free(x);
	} while (*l != ultimo);
	*l = NULL;
}

void l_insFim(Lista* l, int novo) {
	NoLista* n = (NoLista*) malloc(sizeof(NoLista));
	n->numero = novo;
	if (l_underflow(l)) {
		n->proximo = n;
	}
	else {
		n->proximo = (*l)->proximo;
		(*l)->proximo = n;
	}
	*l = n;
}

bool l_remInicio(Lista* l, int* removido) {
	if (l_underflow(l)) {
		return false;
	}
	NoLista* x = (*l)->proximo;
	*removido = x->numero;
	if (x->proximo == x) {
		*l = NULL;
	}
	else {
		(*l)->proximo = x->proximo;
	}
	free(x);
	return true;
}

bool l_underflow(Lista* l) {
	return *l == NULL;
}

void l_imprime(Lista* l) {
	if (l_underflow(l)) {
		return;
	}
	NoLista* x = (*l)->proximo;
	do {
		printf("%d ", x->numero);
		x = x->proximo;
	} while (x != (*l)->proximo);
	putchar('\n');
}

void l_inverte(Lista* l) {
	Pilha auxiliar;
	inicia(&auxiliar);

	while (!l_underflow(l)) {
		int num;
		l_remInicio(l, &num);
		push(&auxiliar, num);
	}
	while (!underflow(&auxiliar)) {
		int num;
		pop(&auxiliar, &num);
		l_insFim(l, num);
	}
}

void inicia(Pilha* p) {
	p->topo = -1;
}

bool push(Pilha* p, int novo) {
	if (overflow(p)) {
		return false;
	}
	p->vetor[++p->topo] = novo;
	return true;
}

bool pop(Pilha* p, int* removido) {
	if (underflow(p)) {
		return false;
	}
	*removido = p->vetor[p->topo--];
	return true;
}

bool underflow(Pilha* p) {
	return p->topo == -1;
}

bool overflow(Pilha* p) {
	return p->topo == MAX_PILHA-1;
}

int main() {
	int vetor[] = { 1, 2, 3, 4, 5, -1 };
	Lista lista;

	l_inicia(&lista);
	int i = 0;
	while (vetor[i] >= 0) {
		l_insFim(&lista, vetor[i]);
		++i;
	}
	printf("Antes da inversao: ");
	l_imprime(&lista);

	l_inverte(&lista);

	printf("Depois da inversao: ");
	l_imprime(&lista);

	l_finaliza(&lista);

	return 0;
}

