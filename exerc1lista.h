#ifndef EXERC1LISTA_H
#define EXERC1LISTA_H

#include <stdbool.h>

// Definicao agnostica do TAD: lista (sem saber como eh implementada)
struct Lista;
struct Noh;

// Interface de operacao do TAD:
struct Lista* cria(void);
void destroi(struct Lista*);
bool underflow(const struct Lista*);
struct Noh* busca(const struct Lista*, int);
void imprime(const struct Lista*);
bool insereInicio(struct Lista*, int);
bool insereFim(struct Lista*, int);
bool insereOrdem(struct Lista*, int);
bool removeInicio(struct Lista*, int*);
bool removeFim(struct Lista*, int*);
bool removeValor(struct Lista*, int);
struct Lista* concatena(struct Lista*, struct Lista*);

#endif
