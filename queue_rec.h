#ifndef QUEUE_REC_H
#define QUEUE_REC_H

struct Queue_;
typedef struct Queue_ Queue;

#include <stdbool.h>
#include <stdlib.h>
#include "record.h"

// Interface /simplificada/ de operacoes do TAD fila
Queue* create(size_t max_elements);
void destroy(Queue* queue);
bool enqueue(Queue* queue, const Record* element); // fila de /enderecos/ dos registros
Record* dequeue(Queue* queue);
bool underflow(const Queue* queue);

#endif // QUEUE_REC_H