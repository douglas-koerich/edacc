#include <stdlib.h>
#include <stdio.h>
#include "exerc1lista.h"

struct Noh {
	int valor;
	struct Noh* proximo;
};

struct Lista {
	struct Noh* cabeca;	// 'cabeca' eh o primeiro noh da lista
};

struct Lista* cria(void) {
	struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
	l->cabeca = NULL;	// lista inicialmente vazia
	return l;
}

bool underflow(const struct Lista* l) {
	return l->cabeca == NULL;
}

void destroi(struct Lista* l) {
	while (l->cabeca != NULL) {
		struct Noh* primeiro = l->cabeca;
		l->cabeca = primeiro->proximo;
		free(primeiro);
	}
	free(l);
}

struct Noh* busca(const struct Lista* l, int x) {
	struct Noh* cursor = l->cabeca;
	while (cursor != NULL) {
		if (cursor->valor == x) {
			break;
		}
		cursor = cursor->proximo;
	}
	return cursor;
}

void imprime(const struct Lista* l) {
	printf("Inicio---%p--->", l->cabeca);
	struct Noh* cursor = l->cabeca;
	while (cursor != NULL) {
		printf("%d---%p--->", cursor->valor, cursor->proximo);
		cursor = cursor->proximo;
	}
	putchar('\n');
}

bool insereInicio(struct Lista* l, int novo) {
	if (busca(l, novo) != NULL) {
		return false;	// jah existe
	}
	struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
	n->valor = novo;
	n->proximo = l->cabeca;
	l->cabeca = n;
	return true;
}

bool removeInicio(struct Lista* l, int* rem) {
	if (l->cabeca == NULL) {
		return false;
	}
	struct Noh* primeiro = l->cabeca;
	*rem = primeiro->valor;
	l->cabeca = primeiro->proximo;
	free(primeiro);
	return true;
}

bool insereFim(struct Lista* l, int novo) {
	if (busca(l, novo) != NULL) {
		return false;	// jah existe
	}
	struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
	n->valor = novo;
	n->proximo = NULL;
	if (l->cabeca == NULL) {
		l->cabeca = n;
		return true;
	}
	struct Noh* ultimo = l->cabeca;
	while (ultimo->proximo != NULL) {	// nao eh o ultimo?
		ultimo = ultimo->proximo;
	}
	ultimo->proximo = n;
	return true;
}

bool removeFim(struct Lista* l, int* rem) {
	if (l->cabeca == NULL) {
		return false;
	}
	struct Noh* ultimo = l->cabeca;
	struct Noh* anterior = NULL;	// nao existe anterior ao
									// primeiro noh
	while (ultimo->proximo != NULL) {
		anterior = ultimo;
		ultimo = ultimo->proximo;
	}
	*rem = ultimo->valor;
	free(ultimo);
	if (anterior != NULL) {	// se o ultimo nao era o primeiro
		anterior->proximo = NULL;
	}
	return true;
}

bool insereOrdem(struct Lista* l, int novo) {
	if (busca(l, novo) != NULL) {
		return false;	// jah existe
	}
	struct Noh* n = (struct Noh*) malloc(sizeof(struct Noh));
	n->valor = novo;
	n->proximo = NULL;
	if (l->cabeca == NULL) {
		l->cabeca = n;
		return true;
	}
	struct Noh* cursor = l->cabeca;
	struct Noh* anterior = NULL;
	while (cursor->valor < novo && cursor->proximo != NULL) {
		anterior = cursor;
		cursor = cursor->proximo;
	}
	// Agora precisa decidir por qual motivo saiu do laco
	if (cursor->valor >= novo) {	// encontrou um noh para vir depois do novo?
		n->proximo = cursor;
		if (anterior != NULL) {	// esse noh encontrado nao eh o primeiro?
			anterior->proximo = n;
		}
		else {
			l->cabeca = n;
		}
	}
	else {	// saiu do laco porque acabou a lista, e os existentes eram todos menores...
		cursor->proximo = n;
	}
	return true;
}

bool removeValor(struct Lista* l, int x) {
	struct Noh* cursor = l->cabeca;
	struct Noh* anterior = NULL;
	while (cursor != NULL && cursor->valor != x) {
		anterior = cursor;
		cursor = cursor->proximo;
	}
	// Novamente precisa decidir porque saiu do laco
	if (cursor == NULL) {
		return false;	// nao achou o valor na lista
	}
	if (anterior == NULL) {
		// Achou valor no primeiro noh
		l->cabeca = cursor->proximo;
	}
	else {
		anterior->proximo = cursor->proximo;
	}
	free(cursor);
	return true;
}

struct Lista* concatena(struct Lista* l1, struct Lista* l2) {
	// Se a lista original (L1) estah vazia, retorna o ponteiro da
	// lista a ser concatenada (L2)
	if (l1 == NULL) {
		return l2;
	}
	// Idem para o caso de L2 estar vazia
	if (l2 == NULL) {
		return l1;
	}
	// Percorre toda a lista L1, removendo da lista L2 os valores duplicados
	struct Noh* cursor = l1->cabeca;
	while (cursor != NULL) {
		removeValor(l2, cursor->valor);
		cursor = cursor->proximo;
	}
	// Agora, busca o ultimo noh de L1
	cursor = l1->cabeca;
	while (cursor->proximo != NULL) {
		cursor = cursor->proximo;
	}
	cursor->proximo = l2->cabeca;
	free(l2);	// NAO destroi, apenas libera o ponteiro externo!
	return l1;
}

