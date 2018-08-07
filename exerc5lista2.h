#ifndef EXERC5LISTA2_H
#define EXERC5LISTA2_H

#include <stdbool.h>

// TAD: Lista linear de numeros reais 
struct Lista;

// Interface RESUMIDA do TAD: lista (apenas as operacoes necessarias para
// a solucao do exercicio e sua demonstracao)
struct Lista* cria(void);
void destroi(struct Lista* l);
bool underflow(const struct Lista* l);
void imprime(const struct Lista* l);
bool inserirInicio(struct Lista* l, float val);

// Operacao pedida pelo exercicio
bool removerIntervalo(struct Lista* l, float inf, float sup);

#endif
