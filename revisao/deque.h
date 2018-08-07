#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

// Definicao das extremidades do deque
typedef enum Lado { INICIO, FIM } Lado;

// Definicao do TAD: deque de inteiros
typedef struct IDeque IDeque;

// Interface do TAD:
IDeque* d_cria(size_t max);
void d_destroi(IDeque* deque);
bool d_underflow(const IDeque* deque);
bool d_overflow(const IDeque* deque);
void d_enqueue(IDeque* deque, int numero, Lado lado);
int d_dequeue(IDeque* deque, Lado lado);
void d_print(const IDeque* deque);

#endif
