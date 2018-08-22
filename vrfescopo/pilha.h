#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdbool.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* cria(void);
void destroi(Pilha*);
void imprime(const Pilha*);
bool underflow(const Pilha*);
bool overflow(const Pilha*);
void push(Pilha*, char);
char pop(Pilha*);

#endif

