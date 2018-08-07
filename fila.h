#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "generico2.h"

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila*);
bool underflow(const Fila*);
bool overflow(const Fila*);
bool enqueue(Fila*, generico*);
generico* dequeue(Fila*);
void imprime(const Fila*);

#endif
