#include <string.h>
#include "queue_rec.h"

struct Queue_ {
    Record* vector;
    size_t max_size;
    int queue_front, queue_rear;
};

Queue* create(size_t max_elements) {
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue->max_size = max_elements;
    new_queue->vector = malloc((max_elements + 1) * sizeof(Record));
    new_queue->queue_front = new_queue->queue_rear = 0;
    return new_queue;
}

void destroy(Queue* queue) {
    while (!underflow(queue)) {
        Record* record = dequeue(queue);
        free(record);
    }
    free(queue->vector);
    free(queue);
}

bool enqueue(Queue* queue, const Record* element) {
    if (queue->queue_front == 0) {
        if (queue->queue_rear == queue->max_size) {
            return false;
        }
    } else {
        if (queue->queue_rear == queue->queue_front - 1) {
            return false;
        }
    }
    memcpy(queue->vector + queue->queue_rear, element, sizeof(Record));
    if (queue->queue_rear == queue->max_size) {
        queue->queue_rear = 0;
    } else {
        ++queue->queue_rear;
    }
    return true;
}

Record* dequeue(Queue* queue) {
    if (underflow(queue)) {
        return NULL;
    }
    Record* element = malloc(sizeof(Record));
    memcpy(element, queue->vector + queue->queue_front, sizeof(Record));
    if (queue->queue_front == queue->max_size) {
        queue->queue_front = 0;
    } else {
        ++queue->queue_front;
    }
    return element;
}

bool underflow(const Queue* queue) {
    return queue->queue_front == queue->queue_rear;
}
