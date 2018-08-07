#ifndef EXERC8LISTA2_H
#define EXERC8LISTA2_H

#include <stdbool.h>

// TAD: Lista CIRCULAR de numeros 
struct Lista;

// Interface RESUMIDA do TAD: lista (apenas as operacoes necessarias para
// a solucao do exercicio e sua demonstracao)
struct Lista* cria(void);
void destroi(struct Lista* l);
bool underflow(const struct Lista* l);
void imprime(const struct Lista* l);
bool inserirFim(struct Lista* l, int val);

// Operacao pedida pelo exercicio
void inverte(struct Lista* l);

#endif
