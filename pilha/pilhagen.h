#ifndef PILHAGEN_H
#define PILHAGEN_H

#include <stdbool.h> // definicao de bool para C
#include <stdlib.h>  // definicao de size_t
#include "tipo.h"    // tipo do elemento armazenado na pilha

// Definicao OPACA (obscura) da implementacao da pilha
typedef struct pilha Pilha;

// Interface de operacoes do TAD pilha
Pilha* cria(size_t); // cria pilha com uma capacidade maxima
void destroi(Pilha*);
void dump(const Pilha*);
bool underflow(const Pilha*); // testa se pilha estah vazia
bool overflow(const Pilha*);  // testa se pilha estah cheia
void push(Pilha*, const Tipo*); // 'Tipo' eh o tipo do elemento armazenado
void pop(Pilha*, Tipo*); // ponteiro do tipo "receberah" o elemento removido

#endif

