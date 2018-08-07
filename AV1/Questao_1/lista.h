/* ESTE ARQUIVO-CABECALHO FOI REPRODUZIDO NO
   ENUNCIADO DA QUESTAO 1 DA PROVA */

#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

struct ListaPalavras;
typedef struct ListaPalavras ListaPalavras;

ListaPalavras* criar(void);
void destruir(ListaPalavras*);
bool underflow(const ListaPalavras*);
void imprimir(const ListaPalavras*);
void inserir(ListaPalavras*, const char*);
void remover(ListaPalavras*, const char*);

#endif  // LISTA_H
