#ifndef PILHAL_H
#define PILHAL_H

#include <stdbool.h>

// TAD: Pilha de numeros
struct Pilha;

// Interface do TAD: pilha
struct Pilha* p_cria(void);
void p_destroi(struct Pilha* l);
bool p_underflow(const struct Pilha* l);
void p_imprime(const struct Pilha* l);
bool push(struct Pilha* l, int val);
bool pop(struct Pilha* l, int* pval);

#endif
