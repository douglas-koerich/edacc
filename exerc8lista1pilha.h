#ifndef EXERC8LISTA1PILHA_H
#define EXERC8LISTA1PILHA_H

#include <stdlib.h> // size_t
#include <stdbool.h>
#include "exerc8lista1tipo.h"

// A pilha serah usada neste exercicio como uma estrutura de dados auxiliar
// para apoiar o processo de inversao dos elementos da fila
struct Pilha;

// Operacoes triviais/convencionais da pilha
struct Pilha* p_cria(size_t);
void p_destroi(struct Pilha*);
bool p_underflow(const struct Pilha*);
bool p_overflow(const struct Pilha*);
bool push(struct Pilha*, tipo);
bool pop(struct Pilha*, tipo*);

// Operacao extra: imprimir a pilha (para debug)
void p_imprime(const struct Pilha*);

#endif

