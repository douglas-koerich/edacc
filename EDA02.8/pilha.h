#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* cria_p(void);
void destroi_p(Pilha*);
bool underflow_p(const Pilha*);
bool overflow_p(const Pilha*);
void imprime_p(const Pilha*);

void push(Pilha*, int);
int pop(Pilha*);

#endif // PILHA_H

