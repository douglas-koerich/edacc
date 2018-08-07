#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exerc6.h"

void inicia(Lista* l) {
	*l = NULL;
}

void finaliza(Lista* l) {
	if (underflow(l)) {
		return;
	}
	NohLista* ultimo = *l;
	do {
		NohLista* x = *l;
		*l = x->proximo;
		free(x);
	} while (*l != ultimo);
}

bool underflow(const Lista* l) {
	return *l == NULL;
}

void insere(Lista* l, int novo_codigo, const char* novo_titulo) {
	// Crio e preencho o novo noh
	NohLista* n = (NohLista*) malloc(sizeof(NohLista));
	n->codigo = novo_codigo;
	strcpy(n->titulo, novo_titulo);

	// Se a lista estah vazia, nao ha o que comparar
	if (underflow(l)) {
		*l = n->proximo = n;
		return;
	}
	// Inicia pelo primeiro noh o percurso na lista
	NohLista* x = (*l)->proximo, *ant = *l;

	// Devo continuar o percurso enquanto:
	// a) Encontro um noh na lista com codigo maior que o meu; ou...
	while (n->codigo > x->codigo) {
		ant = x;
		x = x->proximo;
		if (x == (*l)->proximo) {
			// b) Voltei ao primeiro depois de percorrer toda a lista (ou
			// seja, meu codigo eh maior que todos; insiro no fim da lista
			// e encerro
			n->proximo = (*l)->proximo;
			(*l)->proximo = n;
			*l = n;
			return;
		}
	}
	// Para estar aqui no codigo foi por causa de (a), nao de (b); tenho
	// que me colocar antes do noh com que me comparei
	n->proximo = x;
	ant->proximo = n;

	// Devo checar pra ver se esse noh que tem codigo maior jah nao eh
	// o primeiro, pois nesse caso tenho que atualizar tambem o ponteiro
	// externo
	if (x == (*l)->proximo) {
		*l = n;
	}
}

void imprime(const Lista* l) {
	if (underflow(l)) {
		return;
	}
	NohLista* x = (*l)->proximo;
	do {
		printf("%d - %s\n", x->codigo, x->titulo);
		x = x->proximo;
	} while (x != (*l)->proximo);
}

int main() {
	Lista acervo;
	inicia(&acervo);

	insere(&acervo, 4, "Iracema");
	insere(&acervo, 2, "Dom Casmurro");
	insere(&acervo, 3, "A Escrava Isaura");
	insere(&acervo, 1, "O Alienista");
	insere(&acervo, 5, "O Guarani");

	imprime(&acervo);

	finaliza(&acervo);
	return 0;
}

