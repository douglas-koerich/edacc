#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

struct Pilha;
typedef struct Pilha Pilha;

Pilha* cria_p(void); // pra nao confundir com a funcao 'cria' da fila
void destroi_p(Pilha*); // idem para 'destroi'
bool underflow_p(const Pilha*); // ibidem para 'underflow'
bool push(Pilha*, char);
bool pop(Pilha*, char*);

#endif // PILHA_H

