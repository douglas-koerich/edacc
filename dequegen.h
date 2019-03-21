#ifndef DEQUEGEN_H
#define DEQUEGEN_H

#include <stdbool.h> // definicao de bool para C
#include <stdlib.h>  // definicao de size_t
#include "tipo.h"    // tipo do elemento armazenado no deque

// Definicao (restritiva) das extremidades (locais) onde se fazem
// as operacoes no TAD deque
enum extremidade { INICIO /*=0*/, FIM /*=1*/ };
typedef enum extremidade Lado;

// Definicao OPACA (obscura) da implementacao do deque
typedef struct deque Deque;

// Interface de operacoes do TAD deque
Deque* cria_d(size_t); // cria deque com uma capacidade maxima
void destroi_d(Deque*);
void dump_d(const Deque*);
bool underflow_d(const Deque*); // testa se deque estah vazio
bool overflow_d(const Deque*);  // testa se deque estah cheio
void enqueue_d(Deque*, const Tipo*, Lado); // 'Tipo' eh o tipo do elemento armazenado
void dequeue_d(Deque*, Tipo*, Lado); // ponteiro do tipo "receberah" o elemento removido

#endif

