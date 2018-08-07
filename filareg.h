#ifndef FILAREG_H
#define FILAREG_H

#include <stdbool.h>
#include "registro.h"

struct Fila;

struct Fila* criar(void);
void destruir(struct Fila* f);
bool underflow(struct Fila* f);
bool enqueue(struct Fila* f, const R* reg);
bool dequeue(struct Fila* f, R* reg);

#endif
