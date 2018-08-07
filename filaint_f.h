#ifndef FILAINT_H
#define FILAINT_H

#include <stdbool.h>
#include "dequeint.h"

// Fila implementada atraves de um deque
typedef struct DequeInt FilaInt;

FilaInt* cria_f(void);
void destroi_f(FilaInt*);
bool underflow_f(const FilaInt*);
bool overflow_f(const FilaInt*);
void enqueue_f(FilaInt*, int);
int dequeue_f(FilaInt*);
void print_f(const FilaInt*);

#endif // FILAINT_H
