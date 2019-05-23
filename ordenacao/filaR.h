#ifndef FILAR_H
#define FILAR_H

#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

typedef struct fila Fila;

Fila* cria(size_t);
void destroi(Fila*);
bool underflow(const Fila*);
bool overflow(const Fila*);
void enqueue(Fila*, const R*);
void dequeue(Fila*, R*);

#endif

