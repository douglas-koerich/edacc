#include <stdio.h>
#include <limits.h>
#include "queue.h"

struct Queue_ {
    unsigned* vector;
    size_t max_size;
    int queue_front, queue_rear;
};

Queue* create_q(size_t max_elements) {
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue->max_size = max_elements;
    new_queue->vector = malloc((max_elements + 1) * sizeof(unsigned));
    new_queue->queue_front = new_queue->queue_rear = 0;
    return new_queue;
}

void destroy_q(Queue* queue) {
    free(queue->vector);
    free(queue);
}

bool enqueue(Queue* queue, unsigned element) {
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

unsigned dequeue(Queue* queue) {
    if (underflow_q(queue)) {
        return UINT_MAX;
    }
    int element = queue->vector[queue->queue_front];
    if (queue->queue_front == queue->max_size) {
        queue->queue_front = 0;
    } else {
        ++queue->queue_front;
    }
    return element;
}

unsigned front(const Queue* queue) {
    if (underflow_q(queue)) {
        return UINT_MAX;
    }
    return queue->vector[queue->queue_front];
}

unsigned rear(const Queue* queue) {
    if (underflow_q(queue)) {
        return UINT_MAX;
    }
    int pos_rear = queue->queue_rear == 0? queue->max_size: queue->queue_rear - 1;
    return queue->vector[pos_rear];
}

size_t size_q(const Queue* queue) {
    return (queue->max_size + 1 - queue->queue_front + queue->queue_rear) % (queue->max_size + 1);
}

bool underflow_q(const Queue* queue) {
    return queue->queue_front == queue->queue_rear;
}

void print_q(const Queue* queue) {
    int i = queue->queue_front;
    while (i != queue->queue_rear) {
        printf("%u ", queue->vector[i]);
        if (i == queue->max_size) {
            i = 0;
        } else {
            ++i;
        }
    }
}
