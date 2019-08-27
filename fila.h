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

#endif // FILA_H
