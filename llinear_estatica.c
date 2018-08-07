#include <stdlib.h>
#include <stdio.h>
#include "llinear_estatica.h"

ListaEstatica iniciaLista(unsigned max) {
	ListaEstatica nova;
	nova.sequencia = (TipoElemento*) malloc(sizeof(TipoElemento) * max);
	nova.max_elementos = max;
	nova.num_elementos = 0;
	return nova;
}

void finalizaLista(ListaEstatica* lista) {
	free(lista->sequencia);
}

void imprimir(const ListaEstatica* lista) {
	putchar('\n');
	for (unsigned indice = 0; indice < lista->num_elementos; ++indice) {
		printf("{%d:%d} ", lista->sequencia[indice].chave, lista->sequencia[indice].campo);
	}
	putchar('\n');
}

TipoElemento* busca(const ListaEstatica* lista, unsigned int chave) {
	for (unsigned indice = 0; indice < lista->num_elementos; ++indice) {
		if (lista->sequencia[indice].chave == chave) {
			return &lista->sequencia[indice];
		}
	}
	return NULL;	// nao existe a "chave" informada na sequencia
}

int inserir(ListaEstatica* lista, TipoElemento novo) {
	if (lista->num_elementos == lista->max_elementos) {
		return 0;	// retorna falso porque nao inseriu (falta espaco)
	}
	// Como a lista eh nao ordenada, basta inserir no fim do vetor
	// Repare que nao estamos cuidando para ter chaves duplicadas
	lista->sequencia[lista->num_elementos].chave = novo.chave;
	lista->sequencia[lista->num_elementos].campo = novo.campo;
	++lista->num_elementos;
	return 1;
}

void remover(ListaEstatica* lista, unsigned int chave) {
	unsigned indice = 0;
	while (indice < lista->num_elementos) {
		if (lista->sequencia[indice].chave == chave) {
			// Transfere todos os seguintes para a sua posicao anterior
			while (indice < lista->num_elementos-1) {
				lista->sequencia[indice].chave = lista->sequencia[indice+1].chave;
				lista->sequencia[indice].campo = lista->sequencia[indice+1].campo;
				++indice;
			}
			--lista->num_elementos;
			return;
		}
		++indice;
	}
}

