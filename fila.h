#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>
#include <stdlib.h>

struct fila {
	int* vetor;
	size_t max;
	int inicio, fim;
};
typedef struct fila Fila;

void inicia(Fila*, size_t);
void finaliza(Fila*);
bool underflow(const Fila*);
bool overflow(const Fila*);
bool enqueue(Fila*, int);
bool dequeue(Fila*, int*);
void imprime(const Fila*);
size_t tamanho(const Fila*);

#endif

