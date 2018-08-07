#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include "generico2.h"

struct Deque;
typedef struct Deque Deque;

enum Extremidade { INICIO, FIM };
typedef enum Extremidade Extremidade;

Deque* cria(void);
void destroi(Deque*);
bool underflow(const Deque*);
bool overflow(const Deque*);
bool enqueue(Deque*, Extremidade, generico*);
generico* dequeue(Deque*, Extremidade);
void imprime(const Deque*);

#endif
