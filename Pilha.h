#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>
#include <stdbool.h>

// Definicao do tipo: Pilha (de caracteres)
struct Pilha;

// Definicao das operacoes (interface do TAD)
struct Pilha* criar(size_t max);
void destruir(struct Pilha* p);
bool push(struct Pilha* p, char c);
char pop(struct Pilha* p);
bool underflow(struct Pilha* p);
bool overflow(struct Pilha* p);

#endif	// PILHA_H

