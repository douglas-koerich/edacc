#ifndef PILHA_H_
#define PILHA_H_

#include <stdbool.h>
#include <stdlib.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* p_cria(void);
void p_destroi(Pilha* pilha);
void push(Pilha* pilha, int elemento);
int pop(Pilha* pilha);
bool p_underflow(const Pilha* pilha);

#endif // PILHA_H_

