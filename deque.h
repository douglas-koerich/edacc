#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

// Definicao das extremidades do deque
typedef enum Lado { ESQ, DIR } Lado;

// Definicao do TAD: deque de inteiros
typedef struct IDeque IDeque;

// Capacidade maxima do deque
#define MAX_ELEMENTOS   20

// Interface do TAD:
IDeque* cria();
void destroi(IDeque* deque);
bool underflow(const IDeque* deque);
bool overflow(const IDeque* deque);
void insere(IDeque* deque, int numero, Lado lado);
int remove_(IDeque* deque, Lado lado);  // pra nao confundir com remove() do stdio.h
void print(const IDeque* deque);

#endif
