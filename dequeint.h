#ifndef DEQUEINT_H
#define DEQUEINT_H

#include <stdbool.h>

enum Extremo { ESQUERDO, DIREITO };
typedef enum Extremo Extremo;

struct DequeInt;
typedef struct DequeInt DequeInt;

DequeInt* cria_d(void);
void destroi_d(DequeInt*);
bool underflow_d(const DequeInt*);
bool overflow_d(const DequeInt*);
void enqueue_d(DequeInt*, Extremo, int);
int dequeue_d(DequeInt*, Extremo);
void print_d(const DequeInt*);

#endif // DEQUEINT_H
