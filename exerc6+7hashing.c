#include <stdlib.h>
#include "exerc6+7hashing.h"

int h(int x) {
	int i = (x - 900)/61 + 1;	// formula da funcao de hashing
	return i % M;				// limitar posicao ao intervalo 0 a M-1
}

int h_(int x, int i) {
	int j = i + 1;	// tentativa linear
	return j % M;	// para limitar posicao ao intervalo 0 a M-1
}

TabelaHashing criar(void) {
	TabelaHashing t = (st_Posicao*) malloc(M*sizeof(st_Posicao));
	if (t != NULL) {
		int i;
		for (i=0; i<M; ++i) {
			(t+i)->estado = VAZIA;	// deixa vetor "preparado"
		}
	}
	return t;
}

int inserir(TabelaHashing t, int x) {
	int i = h(x), j = i;	// calcula posicao original usando h(x)
	while ((t+j)->estado == OCUPADA) {	// colisao!
		j = h_(x, j);	// enderecamento aberto por tentativa linear
		if (j == i) {	// se voltou para posicao original, tabela cheia!
			return -1;	// nao inseriu, devolve posicao invalida
		}
	}
	(t+j)->estado = OCUPADA;
	(t+j)->chave = x;
	return j;			// inseriu, devolve a posicao onde armazenou
}

int buscar(TabelaHashing t, int x) {
	int i = h(x), j = i;	// primeira posicao onde vai buscar
	do {
		switch ((t+j)->estado) {
			case VAZIA:		// fim da sequencia (nao ha proximas)
				return -1;	// nao achou a chave procurada

			case OCUPADA:
				if ((t+j)->chave == x) {
					return j;	// achei na posicao j
				}
				else {
					j = h_(x, j);	// achei outra (sinonima?), proxima...
				}
				break;

			case LIBERADA:
			default:
				j = h_(x, j);	// esta vazia, mas tem proxima(s)...
		}
	} while (j != i);
	return -1;	// voltou a posicao original sem achar a chave
}

int remover(TabelaHashing t, int x) {
	int i = buscar(t, x);	// busca a chave na tabela (usando hashing)
	if (i != -1) {			// encontrou?
		(t+i)->estado = LIBERADA;	// simplesmente libera a posicao
	}
	return i;
}

void destruir(TabelaHashing t) {
	free(t);
}

