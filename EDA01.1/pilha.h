#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdbool.h>
#include <stdlib.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* cria(void);
void destroi(Pilha*);
void imprime(const Pilha*);
bool underflow(const Pilha*);
bool overflow(const Pilha*);
void push(Pilha*, int);
int pop(Pilha*);

// Solucao do exercicio 1: nova operacao no TAD
size_t tamanho(const Pilha*);

#endif

