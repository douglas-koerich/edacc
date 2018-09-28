#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

struct Lista;
typedef struct Lista Lista;

Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
bool overflow(const Lista*);
void imprime(const Lista*);
bool busca(const Lista*, int);

enum Posicao { INICIO, FIM, ORDEM, VALOR };
typedef enum Posicao Posicao;

void inserir(Lista*, int, Posicao);
int remover(Lista*, int, Posicao);

/**
 * NOVA OPERACAO SOLICITADA PELO EXERCICIO 8 DA LISTA
 */
void inverte(Lista*);

#endif // LISTA_H

