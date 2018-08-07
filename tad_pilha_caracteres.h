#ifndef TAD_PILHA_H
#define TAD_PILHA_H

#include <stdbool.h>

struct PilhaChar;
typedef struct PilhaChar PilhaChar;

PilhaChar* cria_pilha(void);
void destroi_pilha(PilhaChar* p);
void imprime_pilha(const PilhaChar* p);
bool underflow(const PilhaChar* p);
bool overflow(const PilhaChar* p);
void push(PilhaChar* p, char ch);
char pop(PilhaChar* p);

#endif
