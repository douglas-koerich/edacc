#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila*);
bool underflow(const Fila*);
bool enqueue(Fila*, char);
bool dequeue(Fila*, char*);

// EXTRA
bool overflow(const Fila*);
#ifdef DEBUG
void imprime(const Fila*);
#endif

#ifdef EX6L1
#include <stdlib.h>
size_t size(const Fila*);
#endif // EX6L1

// Questao #2 da Prova do 1o. Bimestre
void mantem_exclusivos(Fila*, Fila*);

#endif // FILA_H
