#ifndef PILHAINT_H
#define PILHAINT_H

#include <stdbool.h>
#include "dequeint.h"

// Pilha implementada atraves de um deque
typedef struct DequeInt PilhaInt;

PilhaInt* cria_p(void);
void destroi_p(PilhaInt*);
bool underflow_p(const PilhaInt*);
bool overflow_p(const PilhaInt*);
void push(PilhaInt*, int);
int pop(PilhaInt*);
void print_p(const PilhaInt*);

#endif // PILHAINT_H
