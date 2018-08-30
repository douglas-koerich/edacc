#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdbool.h>
#include <stdlib.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* criap(void);
void destroip(Pilha*);
void imprimep(const Pilha*);
bool underflowp(const Pilha*);
bool overflowp(const Pilha*);
void push(Pilha*, int);
int pop(Pilha*);

#endif

