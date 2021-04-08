#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include <stdlib.h>
#include "elemento.h"

struct fila;
typedef struct fila Fila;

void enqueue(Fila*, TipoElemento);
TipoElemento dequeue(Fila*);
TipoElemento front(const Fila*);
TipoElemento rear(const Fila*);
size_t size(const Fila*);
bool underflow(const Fila*);

Fila* create(void);
void destroy(Fila*);
void print(const Fila*);

#endif // FILA_H