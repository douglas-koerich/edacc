#include <stdio.h>
#include <stdlib.h>
#include "lcirc.h"
#include "exerc5.h"

/*
 * Implementacao do TAD auxiliar: pilha de nohs (enderecos)
 */

void iniciaP(Pilha* p) {
	*p = NULL;
}

void finalizaP(Pilha* p) {
	if (underflowP(p)) {
		return;
	}
	while (*p != NULL) {
		NoP* q = *p;
		*p = q->proximo;
		free(q);
	}
	*p = NULL;
}

bool underflowP(const Pilha* p) {
	return *p == NULL;
}

void push(Pilha* p, const No* novo) {
	NoP* n = (NoP*) malloc(sizeof(NoP));
	n->valor = novo;
	n->proximo = *p;
	*p = n;
}

bool pop(Pilha* p, const No** noh) {
	NoP* n = *p;
	if (underflowP(p)) {
		return false;
	}
	*noh = n->valor;
	*p = n->proximo;
	free(n);
	return true;
}

/*
 * Implementacao da solucao do exercicio 5: inverte()
 * Vamos fazer da funcao parte do TAD: lista circular
 */
void inverte(Lista* l) {
	// Note na definicao da pilha auxiliar que vamos empilhar
	// os enderecos "proximo", e nao valores int dos nohs;
	// assim, soh o que precisaremos fazer eh apontar com o
	// "proximo" o noh *anterior* da lista
	Pilha pilha;
	No* q;
	if (underflow(l)) {
		return;
	}
	iniciaP(&pilha);

	// Comeca do inicio da lista
	q = (*l)->proximo;
	do {
		// Vai guardando o inicio do 1o., 2o., 3o., ate o
		// endereco do ultimo no
		push(&pilha, q);
		q = q->proximo;
	} while (q != (*l)->proximo);

	// Paramos o laco anterior no ponto onde comecamos, o
	// inicio da lista; agora, desempilhamos o endereco da
	// pilha (o primeiro topo eh o endereco do ultimo no) e
	// pomos esse endereco no campo "proximo", e vamos nessa
	// direcao (de tras pra frente) desempilhando
	while (!underflowP(&pilha)) {
		pop(&pilha, (const No**) &q->proximo);
		q = q->proximo;
	}
	// O laco acima vai parar sobre aquele noh que era o
	// primeiro (inicio) antes da inversao; ele eh o novo fim,
	// portanto o ponteiro externo tem que apontar pra ele
	*l = q;

	finalizaP(&pilha);
}

