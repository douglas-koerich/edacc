#ifndef FILA_H
#define FILA_H

#include <stdbool.h>	// bool
#include <stdlib.h>		// size_t

// Somente a definicao da estrutura para permitir a compilacao
struct Fila;

// Prototipos da interface do TAD
struct Fila* cria(size_t);
void destroi(struct Fila*);
bool overflow(const struct Fila*);	// fila cheia?
bool underflow(const struct Fila*);	// fila vazia?
bool enqueue(struct Fila*, int);	// insere int na fila de inteiros
bool dequeue(struct Fila*, int*);	// remove da fila para o endereco
void print(const struct Fila*);

#endif	// FILA_H
