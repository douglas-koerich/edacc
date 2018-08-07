#ifndef FILA_NUM_H
#define FILA_NUM_H

#include <stdbool.h>
#include "registro.h"

// TAD: Fila de registros

#define MAX_ELEMENTOS   50

// Definicao abstrata do tipo (opaco)
struct Fila_reg;
typedef struct Fila_reg Fila_reg;

// Operacoes do TAD
Fila_reg* cria(void);
void destroi(Fila_reg* f);
bool underflow(const Fila_reg* f);
bool overflow(const Fila_reg* f);
void enqueue(Fila_reg* f, const Registro*);
Registro* dequeue(Fila_reg* f);

#endif  // FILA_NUM_H
