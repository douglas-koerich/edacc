#ifndef TAD_LISTA_LINEAR_H
#define TAD_LISTA_LINEAR_H

#include <stdbool.h>

struct ListaInt;
typedef struct ListaInt ListaInt;

ListaInt* criar(void);
void destruir(ListaInt* l);
bool underflow(const ListaInt* l);
void imprimir(const ListaInt* l);
void inserir_cabeca(ListaInt* l, int n);
int remover_cabeca(ListaInt* l);

// Exercicio 7 da lista
size_t tamanho(const ListaInt* l);

// Exercicio 8 da lista
void inverter(ListaInt* l);

#endif
