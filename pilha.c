#include <stdlib.h>
#include "pilha.h"

int p_criar(Pilha* p, size_t n) {
	p->elementos = (int*) malloc(n * sizeof(int));
	if (p->elementos == NULL) {
		return 0;
	}
	p->tamanho = n;
	p->topo = -1;
	return 1;
}

void p_destruir(Pilha* p) {
	if (p->elementos != NULL) {
		free(p->elementos);
	}
	p->tamanho = 0;
	p->topo = -1;
}

int p_cheia(const Pilha* p) {
	return p->topo == p->tamanho-1;
}

int p_vazia(const Pilha* p) {
	return p->topo == -1;
}

int p_inserir(Pilha* p, int v) {
	if (p_cheia(p)) {
		return 0;	/* Nao pode inserir em pilha cheia */
	}
	p->elementos[++p->topo] = v;
	return 1;
}

int p_remover(Pilha* p, int* ev) {
	if (p_vazia(p)) {
		return 0;	/* Nao ha elemento a remover */
	}
	*ev = p->elementos[p->topo--];
	return 1;
}

