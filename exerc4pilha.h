#ifndef EXERC4PILHA_H
#define EXERC4PILHA_H

#include <stdlib.h>
#include <stdbool.h>

struct Pilha;

struct Pilha* cria(size_t);
void destroi(struct Pilha*);
bool underflow(const struct Pilha*);
bool overflow(const struct Pilha*);
bool push(struct Pilha*, int);
bool pop(struct Pilha*, int*);
void print(const struct Pilha*);

#endif

