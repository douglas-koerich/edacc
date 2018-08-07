/**
 * TAD: Lista linear
 * Este arquivo-fonte implementa a real estrutura de dados sem
 * que isto seja disponibilizado (visivel) ao usuario
 */

#include <stdio.h>
#include "Lista.h"

// Definicao da estrutura
struct Lista {
	/* Como a lista eh do tipo SEQUENCIAL, a estrutura-base que suporta
	 * uma lista contigua (sem interrupcoes na memoria) eh naturalmente
	 * um vetor, que alocaremos dinamicamente quando da operacao de
	 * criacao (prevista na interface do TAD) */
	int* vetor;	// vai receber o endereco do vetor alocado dinamicamente
	size_t max;	// para controle de lista cheia
	size_t num;	// contador de elementos na lista
};

// Implementacao das operacoes

struct Lista* criar(size_t max) {
	struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));
	l->num = 0;
	l->max = max;
	l->vetor = (int*) malloc(sizeof(int) * max);
	return l;
}

void destruir(struct Lista* l) {
	// Cuidado com a ordem! Se desalocar l antes, nao podera desalocar
	// o vetor (l->vetor)!
	free(l->vetor);
	free(l);
}

void imprimir(struct Lista* l) {
	int i;
	putchar('\n');
	for (i = 0; i < l->num; ++i) {
		printf("%d ", l->vetor[i]);
	}
	putchar('\n');
}

// Retorna a posicao do valor no vetor da lista,
// ou -1 (posicao invalida) se nao for encontrado
int buscar(struct Lista* l, int valor) {
	int i;
	for (i = 0; i < l->num; ++i) {
		if (l->vetor[i] == valor) {
			return i;
		}
	}
	return -1;
}

// Retorna verdadeiro (1) se valor foi encontrado e removido,
// ou falso (0) se valor nao foi encontrado na lista
int remover(struct Lista* l, int valor) {
	int i;
	for (i = 0; i < l->num; ++i) {
		if (l->vetor[i] == valor) {
			// Remove o valor deslocando a continuacao da lista
			// para esta posicao
			int j;
			for (j = i; j < l->num-1; ++j) {
				l->vetor[j] = l->vetor[j+1];
			}
			--l->num;	// desconta esse valor removido do contador
			return 1;	// encontrou e removeu, retorna verdadeiro
		}
	}
	return 0;	// nao encontrou, retorna falso
}

// Retorna verdadeiro (1) se valor foi acrescentado a lista, senao
// retorna falso (0) pois a lista estah cheia
int adicionar(struct Lista* l, int valor, enum Posicao pos) {
	int i;
	if (l->num == l->max) {
		return 0;	// lista cheia, retorna falso
	}
	// Onde vai adicionar?
	switch (pos) {
		case FIM:
			// Este eh o caso mais facil, basta acrescentar no fim da lista,
			// que ja estah livre
			l->vetor[l->num] = valor;
			break;

		case INICIO:
			// Precisa "abrir espaco" no inicio da lista; desloca todos os
			// elementos ja existentes uma posicao adiante
			for (i = l->num-1; i >= 0; --i) {
				l->vetor[i+1] = l->vetor[i];
			}
			l->vetor[0] = valor;
			break;

		case ORDEM:
			// Procura pelo primeiro numero maior que valor, ou fim da lista
			for (i = 0; i < l->num; ++i) {
				if (l->vetor[i] > valor) {
					break;
				}
			}
			// Saiu do laco no fim da lista?
			if (i == l->num) {
				// Eh como a insercao no fim
				l->vetor[l->num] = valor;
			}
			else {
				// Saiu antes do fim, encontrou valor maior; precisa deslocar
				// a continuacao da lista uma posicao adiante
				int j;
				for (j = l->num-1; j >= i; --j) {
					l->vetor[j+1] = l->vetor[j];
				}
				l->vetor[i] = valor;
			}
			break;
	}
	++l->num;
	return 1;
}

void ordenar(struct Lista* l) {
	// Ordenacao pelo algoritmo de bolha:
	int i, j;
	for (i = 1; i <= l->num; ++i) {
		for (j = l->num-1; j > 0; --j) {
			if (l->vetor[j] < l->vetor[j-1]) {
				int aux = l->vetor[j];
				l->vetor[j] = l->vetor[j-1];
				l->vetor[j-1] = aux;
			}
		}
	}
}
				
