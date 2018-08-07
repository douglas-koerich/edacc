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

void f_inicia(Fila*, size_t);
void f_finaliza(Fila*);
bool f_underflow(const Fila*);
bool f_overflow(const Fila*);
bool enqueue(Fila*, int);
bool dequeue(Fila*, int*);
void f_imprime(const Fila*);
size_t f_tamanho(const Fila*);

#endif

