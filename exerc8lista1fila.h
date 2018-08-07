#ifndef EXERC8LISTA1FILA_H
#define EXERC8LISTA1FILA_H

#include <stdlib.h> // size_t
#include <stdbool.h>
#include "exerc8lista1tipo.h"

struct Fila;

// Operacoes triviais/convencionais da fila
struct Fila* f_cria(size_t);
void f_destroi(struct Fila*);
bool f_underflow(const struct Fila*);
bool f_overflow(const struct Fila*);
bool enqueue(struct Fila*, tipo);
bool dequeue(struct Fila*, tipo*);

// Operacao extra: imprimir a fila (para debug)
void f_imprime(const struct Fila*);

// Operacao adicional pedida pelo exercicio
void f_inverte(struct Fila*);

#endif

