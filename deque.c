#include <stdlib.h>
#include "deque.h"

int d_criar(Deque* d, size_t n) {
	d->elementos = (int*) malloc((n+1) * sizeof(int));
	if (d->elementos == NULL) {
		return 0;
	}
	d->tamanho = n+1;	/* o deque circular "sacrifica" uma posicao */
	d->esq = d->dir = d->tamanho-1;
	return 1;
}

void d_destruir(Deque* d) {
	if (d->elementos != NULL) {
		free(d->elementos);
	}
	d->tamanho = 0;
	d->esq = d->dir = -1;
}

int d_cheio(const Deque* d) {
	return d->dir == (d->esq? d->esq-1: d->tamanho-1);
}

int d_vazio(const Deque* d) {
	return d->esq == d->dir;
}

int d_inserir(Deque* d, Lado l, int v) {
	if (d_cheio(d)) {
		return 0;	/* Nao pode inserir em deque cheio */
	}
	if (l == ESQUERDO) {
		d->esq = d->esq == 0? d->tamanho-1:
				 d->esq - 1;
		d->elementos[d->esq] = v;
	}
	else {
		d->dir = d->dir == d->tamanho-1? 0:
				 d->dir + 1;
		d->elementos[d->dir] = v;
	}
	return 1;
}

int d_remover(Deque* d, Lado l, int* ev) {
	if (d_vazio(d)) {
		return 0;	/* Nao ha elemento a remover */
	}
	if (l == ESQUERDO) {
		d->esq = d->esq == d->tamanho-1? 0:
				 d->esq + 1;
		*ev = d->elementos[d->esq];
	}
	else {
		d->dir = d->dir == 0? d->tamanho-1:
				 d->dir - 1;
		*ev = d->elementos[d->dir];
	}
	return 1;
}

