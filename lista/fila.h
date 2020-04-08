#ifndef FILA_H_
#define FILA_H_

#include <stdbool.h>
#include <stdlib.h>

struct Fila;
typedef struct Fila Fila;

Fila* f_cria(void);
void f_destroi(Fila* fila);
void f_insere(Fila* fila, int elemento);
int f_retira(Fila* fila);
bool f_underflow(const Fila* fila);

#endif // FILA_H_

