#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exerc4.h"

void inicia(Lista* l) {
	*l = NULL;
}

void finaliza(Lista* l) {
	while (*l != NULL) {
		NohLista* x = *l;
		*l = x->proximo;
		free(x);
	}
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
		n->proximo = n->anterior = NULL;
		*l = n;
		return;
	}
	// Inicia o percurso na lista
	NohLista* x = *l, *ant = NULL;

	// Devo continuar o percurso enquanto:
	// a) Nao chego ao fim da lista (o novo codigo eh maior que todos)
	// b) Encontro um noh na lista com codigo maior que o meu
	while (x != NULL && n->codigo > x->codigo) {
		ant = x;
		x = x->proximo;
	}
	// Parei, mas por que? Por causa de (a) ou de (b)?
	// Verifico se foi por causa de (a)
	if (x == NULL) {
		// Sou o novo ultimo da lista
		n->proximo = NULL;
		n->anterior = ant;
		ant->proximo = n;
		return;
	}
	// Nao, parei por causa de (b); tenho que me colocar antes do noh
	// com que me comparei
	n->proximo = x;
	n->anterior = x->anterior;
	x->anterior = n;
	// Devo checar pra ver se esse noh que tem codigo maior jah nao eh
	// o primeiro, pois nesse caso tenho que atualizar tambem o ponteiro
	// externo
	if (n->anterior == NULL) {
		*l = n;
	}
	else {
		n->anterior->proximo = n;
	}
}

void imprime(const Lista* l) {
	NohLista* x = *l;
	while (x != NULL) {
		printf("%d - %s\n", x->codigo, x->titulo);
		x = x->proximo;
	}
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

