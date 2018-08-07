#ifndef TADS_H
#define TADS_H

#include <stdlib.h>
#include <stdbool.h>

/******************************************
 * TAD "Pilha"
 *****************************************/

// Definicao do tipo: Pilha (de caracteres)
struct Pilha;

// Definicao das operacoes (interface do TAD)
struct Pilha* p_criar(size_t max);
void p_destruir(struct Pilha* p);
bool push(struct Pilha* p, char c);
char pop(struct Pilha* p);
bool p_underflow(struct Pilha* p);
bool p_overflow(struct Pilha* p);
void p_imprimir(struct Pilha* p);

/******************************************
 * TAD "Fila" (circular)
 *****************************************/

// Definicao do tipo: Fila (de caracteres)
struct Fila;

// Definicao das operacoes (interface do TAD)
struct Fila* f_criar(size_t max);
void f_destruir(struct Fila* f);
bool enqueue(struct Fila* f, char c);
char dequeue(struct Fila* f);
bool f_underflow(struct Fila* f);
bool f_overflow(struct Fila* f);
void f_imprimir(struct Fila* f);

#endif	// TADS_H

