#ifndef PILHABITS_H
#define PILHABITS_H

#include <stdlib.h>
#include <stdbool.h>

typedef char bit;

struct Pilha;

struct Pilha* cria(size_t numBits);
void destroi(struct Pilha* pilha);
bool underflow(const struct Pilha* pilha);
bool overflow(const struct Pilha* pilha);
bool push(struct Pilha* pilha, bit novo);
bool pop(struct Pilha* pilha, bit* digito);

#endif

