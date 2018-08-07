#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdlib.h>
#include <stdbool.h>

// Definicao do TAD: pilha com alocacao dinamica
struct pilha {
	int* vetor;
	size_t max;
	int topo;
};
typedef struct pilha Pilha;

// Operacoes validas para a estrutura de dados "pilha"
void p_inicia(Pilha*, size_t);
bool p_underflow(const Pilha*);
bool p_overflow(const Pilha*);
bool push(Pilha*, int);
bool pop(Pilha*, int*);
void p_finaliza(Pilha*);
// size_t p_size(const Pilha*);

#endif

