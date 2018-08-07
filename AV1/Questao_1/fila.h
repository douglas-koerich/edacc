#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

struct Fila;
typedef struct Fila Fila;

Fila* cria_fila(void);
void destroi_fila(Fila* f);
bool fila_vazia(const Fila* f);
void enqueue(Fila* f, const char* s);
const char* dequeue(Fila* f);

#endif  // FILA_H
