#ifndef FILA_NUM_H
#define FILA_NUM_H

#include <stdbool.h>

// TAD: Fila de numeros naturais

#define MAX_ELEMENTOS   50

// Definicao abstrata do tipo (opaco)
struct Fila_num;
typedef struct Fila_num Fila_num;

// Operacoes do TAD
Fila_num* cria(void);
void destroi(Fila_num* f);
bool underflow(const Fila_num* f);
bool overflow(const Fila_num* f);
void enqueue(Fila_num* f, unsigned n);
unsigned dequeue(Fila_num* f);

// Extra
void imprime(const Fila_num* f);

#endif  // FILA_NUM_H
