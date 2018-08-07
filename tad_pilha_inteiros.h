#ifndef TAD_PILHA_H
#define TAD_PILHA_H

#include <stdbool.h>

struct PilhaInt;
typedef struct PilhaInt PilhaInt;

PilhaInt* cria_pilha(void);
void destroi_pilha(PilhaInt* p);
void imprime_pilha(const PilhaInt* p);
bool punderflow(const PilhaInt* p);
bool poverflow(const PilhaInt* p);
void push(PilhaInt* p, int num);
int pop(PilhaInt* p);

#endif
