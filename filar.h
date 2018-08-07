#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "registro.h"

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila* f);
bool underflow(const Fila* f);
void enqueue(Fila* f, R r);
R dequeue(Fila* f);

#endif  // FILA_H
