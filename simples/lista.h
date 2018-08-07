#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

// Definicao do tipo armazenado na lista encadeada
typedef int tipo;

// Definicao de um registro invalido
extern const tipo INVALIDO;

// Definicao do TAD: Lista encadeada simples de registros do tipo
struct Lista;
typedef struct Lista Lista;

// Operacoes do TAD (simplificado!)
Lista* cria(void);
void destroi(Lista* l);
bool underflow(const Lista* l);
void insereInicio(Lista* l, tipo novo);
tipo removeInicio(Lista* l);

// Exercicio: nova funcao que conta o numero de ocorrencias do mesmo valor na lista
unsigned numOcorrencias(const Lista* l, tipo valor);

#endif
