#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

// Definicao do TAD: fila de inteiros
typedef struct IFila IFila;

// Interface do TAD:
IFila* cria(size_t max);
void destroi(IFila* fila);
bool underflow(const IFila* fila);
bool overflow(const IFila* fila);
void enqueue(IFila* fila, int numero);
int dequeue(IFila* fila);
void print(const IFila* fila);

#endif
