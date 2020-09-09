#ifndef QUEUE_H
#define QUEUE_H

struct Queue_;
typedef struct Queue_ Queue;

#include <stdbool.h>
#include <stdlib.h>

Queue* create_q(size_t max_elements);
void destroy_q(Queue* queue);
bool enqueue(Queue* queue, unsigned element); // fila de numeros inteiros sem sinal
unsigned dequeue(Queue* queue);
unsigned front(const Queue* queue);
unsigned rear(const Queue* queue);
size_t size_q(const Queue* queue);
bool underflow_q(const Queue* queue);
void print_q(const Queue* queue);

#endif // QUEUE_H