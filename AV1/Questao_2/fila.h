/* ESTE ARQUIVO-CABECALHO FOI REPRODUZIDO NO
   ENUNCIADO DA QUESTAO 2 DA PROVA */

#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

struct FilaInt;
typedef struct FilaInt FilaInt;

FilaInt* criar(void);
void destruir(FilaInt* f);
void imprimir(const FilaInt* f);
bool underflow(const FilaInt* f);
bool overflow(const FilaInt* f);
void enqueue(FilaInt* f, int n);
int dequeue(FilaInt* f);

#endif  // FILA_H
