#ifndef PILHA_CH_H
#define PILHA_CH_H

#include <stdbool.h>

// TAD: Pilha de caracteres
struct PilhaCh;

// Interface: operacoes do TAD
struct PilhaCh* cria(void);
void destroi(struct PilhaCh*);
bool underflow(const struct PilhaCh*);
bool overflow(const struct PilhaCh*);
bool push(struct PilhaCh*, char);
bool pop(struct PilhaCh*, char*);

#endif // PILHA_CH_H

