#ifndef _EXERC5_H_
#define _EXERC5_H_

#include "lcirc.h"

/*
 * Definicao do TAD auxiliar: pilha (encadeada) de nohs (ponteiros)
 */
struct noPilha {
	const No* valor;			// o endereco de um noh da lista circular
	struct noPilha* proximo;	// proximo noh desta pilha
};
typedef struct noPilha NoP;
typedef struct noPilha* Pilha;

void iniciaP(Pilha*);
void finalizaP(Pilha*);
bool underflowP(const Pilha*);
void push(Pilha*, const No*);	// empilha um noh da lista
bool pop(Pilha* p, const No**);	// desempilha um noh
/*
 * Fim do TAD: pilha de nos da lista circular
 */

void inverte(Lista*); 

#endif

