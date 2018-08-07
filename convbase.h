#ifndef _CONVBASE_H_
#define _CONVBASE_H_

#include <stdbool.h>

// Como vamos converter numeros inteiros decimais para binario, o numero
// maximo de bits sera 32 (sizeof(int) = 4); portanto, nao eh necessario
// reservar um vetor para a pilha com mais de 32 posicoes
#define MAX_PILHA	32

// TAD: Pilha de numeros 0s e 1s
struct pilha01 {
	int digitos[MAX_PILHA];	// int -> elemento eh um numero/digito 0 ou 1
	int topo;
};
typedef struct pilha01 Pilha;

void inicia(Pilha*);
bool push(Pilha*, int);
bool pop(Pilha*, int*);
bool overflow(Pilha*);
bool underflow(Pilha*);

#endif
