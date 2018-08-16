#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdbool.h>

// Definicao opaca do TAD para simples referencia de uso pela
// aplicacao que precisa da pilha como estrutura de dados
// OBS.: 'T' eh um tipo qualquer, substitua por char, int, um
// registro especifico, etc.
struct PilhaT;
typedef struct PilhaT PilhaT;

// Interface de uso do TAD, i.e., suas operacoes basicas
PilhaT* cria(void);
void destroi(PilhaT*);
void imprime(const PilhaT*); // exibe a lista de elementos na pilha
bool underflow(const PilhaT*);
bool overflow(const PilhaT*);
void push(PilhaT*, T);
T pop(PilhaT*);

#endif

