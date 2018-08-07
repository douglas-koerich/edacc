#ifndef PILHAINT_H
#define PILHAINT_H

#include <stdbool.h>

struct PilhaInt;
typedef struct PilhaInt PilhaInt;

PilhaInt* cria(void);
void destroi(PilhaInt*);
bool underflow(const PilhaInt*);
bool overflow(const PilhaInt*);
void push(PilhaInt*, int);
int pop(PilhaInt*);

#endif // PILHAINT_H
