#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "generico2.h"  // estrutura com callback de comparacao

struct Pilha;
typedef struct Pilha Pilha;

Pilha* cria(void);
void destroi(Pilha*);
bool underflow(const Pilha*);
bool overflow(const Pilha*);
bool push(Pilha*, generico*);
generico* pop(Pilha*);
void imprime(const Pilha*);

#endif

