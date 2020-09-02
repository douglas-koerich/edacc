#ifndef QUEUE_H
#define QUEUE_H

// Definicao ABSTRATA do tipo fila
struct Queue_;
typedef struct Queue_ Queue;

#include <stdbool.h>
#include <stdlib.h>

// Interface de operacoes do TAD fila
Queue* create(size_t max_elements);
void destroy(Queue* queue);
bool enqueue(Queue* queue, int element); // fila de numeros inteiros
int dequeue(Queue* queue);
int front(const Queue* queue);
int rear(const Queue* queue);
size_t size(const Queue* queue);
bool underflow(const Queue* queue);
void print(const Queue* queue);

#endif // QUEUE_H