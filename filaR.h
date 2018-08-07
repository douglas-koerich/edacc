#ifndef FILAI_H
#define FILAI_H

#include <stdbool.h>
#include "registro.h"

// Fila auxiliar para armazenar os registros ordenados segundo
// o algoritmo radixsort
struct Fila;

struct Fila* criar(void);
bool underflow(struct Fila* f);
bool enqueue(struct Fila* f, const Registro* reg);
bool dequeue(struct Fila* f, Registro* reg);
void destruir(struct Fila* f);

#endif	// FILAI_H

