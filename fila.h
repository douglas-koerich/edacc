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
size_t f_size(const Fila*);
bool f_underflow(const Fila*);

Fila* f_create(void);
void f_destroy(Fila*);
void f_print(const Fila*);

#endif // FILA_H