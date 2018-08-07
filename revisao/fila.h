#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

// Definicao do TAD: fila de inteiros
typedef struct IFila IFila;

// Interface do TAD:
IFila* f_cria(size_t max);
void f_destroi(IFila* fila);
bool f_underflow(const IFila* fila);
bool f_overflow(const IFila* fila);
void f_enqueue(IFila* fila, int numero);
int f_dequeue(IFila* fila);
void f_print(const IFila* fila);

#endif
