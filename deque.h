#ifndef DEQUE_H
#define DEQUE_H

// Definicao ABSTRATA do tipo fila de dupla extremidade
struct Deque_;
typedef struct Deque_ Deque;

#include <stdbool.h>
#include <stdlib.h>

// Enumeracao das extremidades da fila (dupla)
enum Side_ {
    FRONT,  // inicio (em C, numerico igual a 0)
    REAR    // fim (soma 1 ao valor acima)
};
typedef enum Side_ Side;

// Interface de operacoes do TAD fila de dupla extremidade
Deque* create(size_t max_elements);
void destroy(Deque* deque);
bool enqueue(Deque* deque, int element, Side where);
int dequeue(Deque* deque, Side where);
int front(const Deque* deque);
int rear(const Deque* deque);
size_t size(const Deque* deque);
bool underflow(const Deque* deque);
void print(const Deque* deque);

#endif // DEQUE_H