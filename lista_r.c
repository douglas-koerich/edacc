#include <stdlib.h>
#include "lista_r.h"

void inicia(Lista* l) {
	*l = NULL;
}

void finaliza(Lista* l) {
	while (*l != NULL) {
		NohLista* x = *l;
		*l = (*l)->proximo;
		free(x);
	}
}

void insere(Lista* l, int novo) {
	NohLista* n = (NohLista*) malloc(sizeof(NohLista));
	n->numero = novo;
	n->proximo = *l;
	*l = n;
}

NohLista* busca_i(Lista l, int chave) {
	NohLista* x = l;
	while (x != NULL) {
		if (x->numero == chave) {
			break;
		}
		x = x->proximo;
	}
	return x;
}

NohLista* busca_r(NohLista* n, int chave) {
	if (n == NULL) {	// 1a. condicao terminal
		return NULL;
	}
	else if (n->numero == chave) {	// 2a. condicao terminal
		return n;
	}
	else {
		return busca_r(n->proximo, chave);	// Fase ativa (chamada recursiva)
	}
}

#include <stdio.h>

int main() {
	int vetor[] = { 1, 2, 3, 4, 5, -1 }, i = 0;
	Lista lista;

	inicia(&lista);
	while (vetor[i] > 0) {
		insere(&lista, vetor[i]);
		++i;
	}

	if (busca_i(lista, 3) != NULL) {
		puts("Achou iterativamente a chave 3!");
	}
	else {
		puts("NAO achou iterativamente a chave 3!");
	}
	if (busca_r(lista, 3) != NULL) {
		puts("Achou recursivamente a chave 3!");
	}
	else {
		puts("NAO achou recursivamente a chave 3!");
	}

	if (busca_i(lista, 7) != NULL) {
		puts("Achou iterativamente a chave 7!");
	}
	else {
		puts("NAO achou iterativamente a chave 7!");
	}
	if (busca_r(lista, 7) != NULL) {
		puts("Achou recursivamente a chave 7!");
	}
	else {
		puts("NAO achou recursivamente a chave 7!");
	}

	finaliza(&lista);
	return 0;
}

