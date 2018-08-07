#ifndef TAD_LISTA_LINEAR_H
#define TAD_LISTA_LINEAR_H

#include <stdbool.h>

struct ListaInt;
typedef struct ListaInt ListaInt;

ListaInt* criar(void);
void destruir(ListaInt* l);
bool underflow(const ListaInt* l);
void imprimir(const ListaInt* l);
bool existe(const ListaInt* l, int n);
void inserir_cabeca(ListaInt* l, int n);
void inserir_cauda(ListaInt* l, int n);
void inserir_ordem(ListaInt* l, int n);
int remover_cabeca(ListaInt* l);
int remover_cauda(ListaInt* l);
void remover_valor(ListaInt* l, int n);

// Nova operacao do TAD
void concatenar(ListaInt*, ListaInt*);

#endif
