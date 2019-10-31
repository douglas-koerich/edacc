#ifndef FILA_REG_H
#define FILA_REG_H

#include <stdbool.h>
#include "registro.h" // tipo de dado armazenado na fila

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila*);
bool underflow(const Fila*);
bool enqueue(Fila*, const Reg*);
bool dequeue(Fila*, Reg*);

// EXTRA
bool overflow(const Fila*);
void imprime(const Fila*);

#endif // FILA_REG_H
