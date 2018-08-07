#ifndef _CONVBASE_H_
#define _CONVBASE_H_

#include <stdbool.h>

// Como vamos converter numeros inteiros decimais para hexa, o numero
// maximo de digitos (hexa) sera 8; portanto, nao eh necessario
// reservar um vetor para a pilha com mais de 8 posicoes
#define MAX_PILHA	8

// TAD: Pilha de caracteres '0'-'F'
struct pilha16 {
	char digitos[MAX_PILHA];	// char -> elemento sera um digito hexa
	int topo;
};
typedef struct pilha16 Pilha;

void inicia(Pilha*);
bool push(Pilha*, char);	// o tipo em push e pop eh o mesmo do vetor
bool pop(Pilha*, char*);	// dentro da estrutura
bool overflow(Pilha*);
bool underflow(Pilha*);

#endif
