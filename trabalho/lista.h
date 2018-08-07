#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "item.h"

// Definicao do TAD: Lista encadeada simples de registros do tipo Reg
struct Lista;

// Operacoes do TAD
struct Lista* cria(void);
void destroi(struct Lista* l);
bool underflow(const struct Lista* l);
void insereInicio(struct Lista* l, const Item* novo);
void insereFim(struct Lista* l, const Item* novo);
void insereOrdem(struct Lista* l, const Item* novo);
const Item* removeInicio(struct Lista* l);
const Item* removeFim(struct Lista* l);
const Item* removeRegistro(struct Lista* l, const char* chave_busca);
const Item* busca(struct Lista* l, const char* chave_busca);
void imprime(struct Lista* l);

#endif
