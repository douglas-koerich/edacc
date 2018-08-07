#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdlib.h>
#include <stdbool.h>

// Definicao do TAD: pilha com alocacao dinamica
struct pilha {
	char* vetor;
	size_t max;
	int topo;
};
typedef struct pilha Pilha;

// Operacoes validas para a estrutura de dados "pilha"
void inicia(Pilha*, size_t);
bool underflow(const Pilha*);
bool overflow(const Pilha*);
bool push(Pilha*, char);
bool pop(Pilha*, char*);
void finaliza(Pilha*);
// size_t size(const Pilha*);

#endif

