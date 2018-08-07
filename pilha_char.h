#ifndef PILHA_CHAR_H
#define PILHA_CHAR_H

#include <stdbool.h>

// TAD: Pilha de caracteres

// Usuario do TAD pode revisar este tamanho maximo de acordo com sua necessidade
#define MAX_ELEMENTOS_PILHA 50

// Definicao abstrata do tipo (opaco)
struct Pilha_ch;
typedef struct Pilha_ch Pilha_ch;

// Operacoes do TAD
Pilha_ch* cria(void);
void destroi(Pilha_ch* p);
bool underflow(const Pilha_ch* p);
bool overflow(const Pilha_ch* p);
void push(Pilha_ch* p, char c);
char pop(Pilha_ch* p);

#endif  // PILHA_CHAR_H
