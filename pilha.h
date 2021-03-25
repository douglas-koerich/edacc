#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include <stdlib.h>

// Definicao do tipo de elemento que serah armazenado na pilha ("empilhado")
#include "elemento.h"

// TAD: definicao "opaca" (nao-transparente) da estrutura de dados
struct pilha;
typedef struct pilha Pilha;

// Operacoes da pilha (cf. slide)
void push(Pilha*, TipoElemento);
TipoElemento pop(Pilha*);

TipoElemento top(const Pilha*);
size_t size(const Pilha*);
bool underflow(const Pilha*); // retorna 'true' se pilha estiver vazia

// Operacoes associadas a qualquer TAD
Pilha* create(void);
void destroy(Pilha*);

// Outras operacoes auxiliares
void print(const Pilha*);

#endif // PILHA_H