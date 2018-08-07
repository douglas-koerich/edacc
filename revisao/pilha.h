#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

// Definicao do TAD: pilha de inteiros
typedef struct IPilha IPilha;

// Interface do TAD:
IPilha* p_cria(size_t max);
void p_destroi(IPilha* pilha);
bool p_underflow(const IPilha* pilha);
bool p_overflow(const IPilha* pilha);
void push(IPilha* pilha, int numero);
int pop(IPilha* pilha);
void p_print(const IPilha* pilha);

#endif
