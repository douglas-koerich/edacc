#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

struct Fila;
typedef struct Fila Fila;

Fila* cria_f(void);
void destroi_f(Fila*);
bool underflow_f(const Fila*);
bool enqueue(Fila*, char);
bool dequeue(Fila*, char*);

// EXTRA
bool overflow_f(const Fila*);
#ifdef DEBUG
void imprime_f(const Fila*);
#endif

#endif // FILA_H
