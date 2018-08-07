#ifndef TAD_PILHA_H
#define TAD_PILHA_H

#include <stdbool.h>

struct PilhaInt;
typedef struct PilhaInt PilhaInt;

PilhaInt* cria(void);
void destroi(PilhaInt* p);
bool punderflow(const PilhaInt* p);
void push(PilhaInt* p, int n);
int pop(PilhaInt* p);

#endif
