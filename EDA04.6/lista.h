#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include "tipos.h" 

struct Lista;
typedef struct Lista Lista;

// Operacoes (interface) originais do TAD
Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
bool overflow(const Lista*);
void imprime(const Lista*);
TipoReg* busca(const Lista*, TipoChave);

enum Posicao { INICIO, FIM, ORDEM, VALOR };
typedef enum Posicao Posicao;

void inserir(Lista*, TipoChave, const TipoReg*, Posicao);
TipoReg remover(Lista*, TipoChave, Posicao);

// Operacao solicitada pelo exercicio
size_t tamanho(const Lista*);

#endif // LISTA_H

