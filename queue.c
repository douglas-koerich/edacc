#include <stdio.h>
#include <limits.h>
#include "queue.h"

struct Queue_ {
    int* vector;
    size_t max_size;
    int queue_front, // indice que guarda a posicao do elemento do inicio da fila
        queue_rear;  // indice da posicao SEGUINTE ao elemento do fim da fila
};

#include <stdbool.h>
#include <stdlib.h>

Queue* create(size_t max_elements) {
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue->max_size = max_elements;
    new_queue->vector = malloc((max_elements + 1) * sizeof(int)); // aloca posicao extra (nunca ocupada)
    new_queue->queue_front = 0; // fila vazia, onde vai inserir o primeiro elemento
    new_queue->queue_rear = 0; // fila vazia, posicao seguinte eh a primeira do vetor
    return new_queue;
}

void destroy(Queue* queue) {
    free(queue->vector);
    free(queue);
}

bool enqueue(Queue* queue, int element) {
    // Se o indice de fim estiver logo "atras" do indice de inicio,
    // a fila esta cheia
    if (queue->queue_front == 0) {
        if (queue->queue_rear == queue->max_size) {
            return false;
        }
    } else {
        if (queue->queue_rear == queue->queue_front - 1) {
            return false;
        }
    }
    queue->vector[queue->queue_rear] = element;
    if (queue->queue_rear == queue->max_size) {
        queue->queue_rear = 0;
    } else {
        ++queue->queue_rear;
    }
    return true;
}

int dequeue(Queue* queue) {
    if (underflow(queue)) {
        return INT_MIN;
    }
    int element = queue->vector[queue->queue_front];
    if (queue->queue_front == queue->max_size) {
        queue->queue_front = 0;
    } else {
        ++queue->queue_front;
    }
    return element;
}

int front(const Queue* queue) {
    if (underflow(queue)) {
        return INT_MIN;
    }
    return queue->vector[queue->queue_front];
}

int rear(const Queue* queue) {
    if (underflow(queue)) {
        return INT_MIN;
    }
    // Cuida para "apontar" para a posicao anterior do indice queue_rear, que no caso
    // de ter "dado a volta" no vetor (voltando a 0), faz com que o ultimo elemento (fim
    // da fila) esteja na ultima posicao do vetor (max_size)
    int pos_rear = queue->queue_rear == 0? queue->max_size: queue->queue_rear - 1;
    return queue->vector[pos_rear];
}

size_t size(const Queue* queue) {
    return (queue->max_size + 1 - queue->queue_front + queue->queue_rear) % (queue->max_size + 1);
}

bool underflow(const Queue* queue) {
    return queue->queue_front == queue->queue_rear; // inicio alcancou o fim (removeu todos)
}

void print(const Queue* queue) {
    int i = queue->queue_front;
    while (i != queue->queue_rear) {
        printf("%d ", queue->vector[i]);
        if (i == queue->max_size) { // na ultima posicao?
            i = 0;
        } else {
            ++i;
        }
    }
}
