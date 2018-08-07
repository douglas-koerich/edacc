#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

// Definicao do TAD: pilha de inteiros
typedef struct IPilha IPilha;

// Interface do TAD:
IPilha* cria(size_t max);
void destroi(IPilha* pilha);
bool underflow(const IPilha* pilha);
bool overflow(const IPilha* pilha);
void push(IPilha* pilha, int numero);
int pop(IPilha* pilha);
void print(const IPilha* pilha);

#endif
