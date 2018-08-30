#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila*);
void imprime(const Fila*);
bool underflow(const Fila*);
bool overflow(const Fila*);
void enqueue(Fila*, int);
int dequeue(Fila*);

// Solucao do exercicio 6: nova operacao no TAD
size_t tamanho(const Fila*);

#endif

