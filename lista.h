#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

struct ListaInt;
typedef struct ListaInt ListaInt;

enum Extremo { INICIO, FIM };
typedef enum Extremo Extremo;

ListaInt* cria(void);
void destroi(ListaInt*);

bool underflow(const ListaInt*);

void insere(ListaInt*, Extremo, int);
void insere_ordem(ListaInt*, int);
void insere_posicao(ListaInt*, int, int);

/* Porque existe a funcao remove() na biblioteca-padrao da linguagem C,
 * vamos chamar as funcoes de remocao do TAD de exclui() */
int exclui(ListaInt*, Extremo);
int exclui_posicao(ListaInt*, int);
void exclui_valor(ListaInt*, int);

// Busca, na verdade, eh um teste que verifica se o numero estah na lista
bool busca(const ListaInt*, int);

void imprime(const ListaInt*);

/* Para os exercicios 1 e 2 da lista, onde nao eh possivel ter
 * uma lista com duplicatas
 */
void insere_exclusivo(ListaInt*, int);
// Exercicio 1 da lista
void concatena_exclusivas(ListaInt*, ListaInt*);
// Exercicio 2 da lista
bool iguais(const ListaInt*, const ListaInt*);

#endif
