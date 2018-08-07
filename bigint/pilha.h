#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

typedef struct Pilha Pilha;

Pilha* cria();
void destroi(Pilha*);
bool underflow(const Pilha*);
void push(Pilha*, char);
char pop(Pilha*);
void print(Pilha*);

#endif  // PILHA_H
