#ifndef FILAGEN_H
#define FILAGEN_H

#include <stdbool.h> // definicao de bool para C
#include <stdlib.h>  // definicao de size_t
#include "tipo.h"    // tipo do elemento armazenado na fila

// Definicao OPACA (obscura) da implementacao da fila
typedef struct fila Fila;

// Interface de operacoes do TAD fila
Fila* cria(size_t); // cria fila com uma capacidade maxima
void destroi(Fila*);
void dump(const Fila*);
bool underflow(const Fila*); // testa se fila estah vazia
bool overflow(const Fila*);  // testa se fila estah cheia
void enqueue(Fila*, const Tipo*); // 'Tipo' eh o tipo do elemento armazenado
void dequeue(Fila*, Tipo*); // ponteiro do tipo "receberah" o elemento removido

#endif

