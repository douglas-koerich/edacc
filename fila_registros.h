#ifndef FILA_REGISTROS_H
#define FILA_REGISTROS_H

#include <stdbool.h>
#include "registro.h"

struct fila;
typedef struct fila Fila;

void f_enqueue(Fila*, const Registro*);
Registro* f_dequeue(Fila*); // deve liberar a memoria alocada por dequeue
bool f_underflow(const Fila*);
Fila* f_create(void);
void f_destroy(Fila*);

#endif