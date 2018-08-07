#include <stdlib.h>
#include "fila.h"

int f_criar(Fila* f, size_t n) {
	f->elementos = (int*) malloc((n+1) * sizeof(int));
	if (f->elementos == NULL) {
		return 0;
	}
	f->tamanho = n+1;	/* a fila circular "sacrifica" uma posicao */
	f->inicio = f->fim = f->tamanho-1;
	return 1;
}

void f_destruir(Fila* f) {
	if (f->elementos != NULL) {
		free(f->elementos);
	}
	f->tamanho = 0;
	f->inicio = f->fim = -1;
}

int f_cheia(const Fila* f) {
	return f->fim == (f->inicio? f->inicio-1: f->tamanho-1);
}

int f_vazia(const Fila* f) {
	return f->inicio == f->fim;
}

int f_inserir(Fila* f, int v) {
	if (f_cheia(f)) {
		return 0;	/* Nao pode inserir em fila cheia */
	}
	f->fim = f->fim == f->tamanho-1? 0:
			 f->fim + 1;
	f->elementos[f->fim] = v;
	return 1;
}

int f_remover(Fila* f, int* ev) {
	if (f_vazia(f)) {
		return 0;	/* Nao ha elemento a remover */
	}
	f->inicio = f->inicio == f->tamanho-1? 0:
				f->inicio + 1;
	*ev = f->elementos[f->inicio];
	return 1;
}

