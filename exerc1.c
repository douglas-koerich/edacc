#include <stdlib.h>
#include "exerc1.h"

void inicia(Lista* l) {
	*l = NULL;
}
/*
void inicia((NohLista*)* n) {
	*n = NULL;
}
*/

void finaliza(Lista* l) {
	NohLista* x = *l;
	while (x != NULL) {
		NohLista* aux = x;
		x = x->proximo;		// Se eu inverter a ordem entre essas 2 linhas,
		free(aux);			// perco a lista encadeada a partir daqui!!!
	}
	*l = NULL;
}

bool underflow(Lista* l) {
	return *l == NULL;
}
/*
bool underflow(Lista l) {
	return l == NULL;
}
*/

void insInicio(Lista* l, int novo) {
	NohLista* noh = (NohLista*) malloc(sizeof(NohLista));
	noh->numero = novo;
	noh->proximo = *l;
	*l = noh;
}

void insFim(Lista* l, int novo) {
	NohLista* noh = (NohLista*) malloc(sizeof(NohLista));
	noh->numero = novo;
	noh->proximo = NULL;	// vai ser sempre o ultimo
	if (underflow(l)) {
		*l = noh;
		return;
	}
	NohLista* x = *l;	// comeca apontando para o primeiro da lista
	while (x->proximo != NULL) {
		x = x->proximo;
	}
	x->proximo = noh;
}

bool remInicio(Lista* l, int* removido) {
	if (underflow(l)) {
		return false;
	}
	NohLista* x = *l;
	*removido = x->numero;
	*l = x->proximo;	// seja la quem for o segundo elemento, vai ser o primeiro
	free(x);
	return true;
}

bool remFim(Lista* l, int* removido) {
	if (underflow(l)) {
		return false;
	}
	NohLista* x = *l, * x_ant = NULL;
	while (x->proximo != NULL) {
		x_ant = x;
		x = x->proximo;
	}
	*removido = x->numero;
	if (x_ant != NULL) {	// havia um anterior?
		x_ant->proximo = NULL;
	}
	else {					// nao existia tal anterior, o ultimo era o unico!
		*l = NULL;
	}
	free(x);
	return true;
}

int soma(Lista* l) {
	int total = 0;
	NohLista* x = *l;
	while (x != NULL) {		// ja funciona pra testar lista vazia
		total += x->numero;
		x = x->proximo;
	}
	return total;
}

#include <stdio.h>

int main() {
	int teste[] = { 1, 2, 3, 4, 5, -1 };

	Lista lista;
	inicia(&lista);

	int i = 0;
	while (teste[i] > 0) {
		insInicio(&lista, teste[i]);
		++i;
	}

	int s = soma(&lista);
	printf("Soma = %d\n", s);

	finaliza(&lista);
	
	return 0;
}

