#include <stdio.h>
#include <limits.h>
#include "deque.h"

struct Deque_ {
    int* vector;
    size_t max_size;
    int queue_front, // indice que guarda a posicao do elemento do inicio da fila
        queue_rear;  // indice da posicao SEGUINTE ao elemento do fim da fila
};

Deque* create(size_t max_elements) {
    Deque* new_queue = malloc(sizeof(Deque));
    new_queue->max_size = max_elements;
    new_queue->vector = malloc((max_elements + 1) * sizeof(int)); // aloca posicao extra (nunca ocupada)
    new_queue->queue_front = 0; // fila vazia, onde vai inserir o primeiro elemento
    new_queue->queue_rear = 0; // fila vazia, posicao seguinte eh a primeira do vetor
    return new_queue;
}

void destroy(Deque* deque) {
    free(deque->vector);
    free(deque);
}

bool enqueue(Deque* deque, int element, Side where) {
    // Se o indice de fim estiver logo "atras" do indice de inicio,
    // a fila esta cheia
    if (deque->queue_front == 0) {
        if (deque->queue_rear == deque->max_size) {
            return false;
        }
    } else {
        if (deque->queue_rear == deque->queue_front - 1) {
            return false;
        }
    }
    // Implementacao original onde a insercao eh feita no FIM da fila
    if (where == REAR) {
        deque->vector[deque->queue_rear] = element;
        if (deque->queue_rear == deque->max_size) {
            deque->queue_rear = 0;
        } else {
            ++deque->queue_rear;
        }
    } else { // Insercao no INICIO (soh existe na fila dupla)
        if (deque->queue_front == 0) {
            deque->queue_front = deque->max_size;
        } else {
            --deque->queue_front;
        }
        deque->vector[deque->queue_front] = element;
    }
    return true;
}

int dequeue(Deque* deque, Side where) {
    if (underflow(deque)) {
        return INT_MIN;
    }
    int element;

    // Implementacao original onde a remocao eh feita do INICIO da fila
    if (where == FRONT) {
        element = deque->vector[deque->queue_front];
        if (deque->queue_front == deque->max_size) {
            deque->queue_front = 0;
        } else {
            ++deque->queue_front;
        }
    } else {
        if (deque->queue_rear == 0) {
            deque->queue_rear = deque->max_size;
        } else {
            --deque->queue_rear;
        }
        element = deque->queue_rear;
    }
    return element;
}

int front(const Deque* deque) {
    if (underflow(deque)) {
        return INT_MIN;
    }
    return deque->vector[deque->queue_front];
}

int rear(const Deque* deque) {
    if (underflow(deque)) {
        return INT_MIN;
    }
    // Cuida para "apontar" para a posicao anterior do indice queue_rear, que no caso
    // de ter "dado a volta" no vetor (voltando a 0), faz com que o ultimo elemento (fim
    // da fila) esteja na ultima posicao do vetor (max_size)
    int pos_rear = deque->queue_rear == 0? deque->max_size: deque->queue_rear - 1;
    return deque->vector[pos_rear];
}

size_t size(const Deque* deque) {
    return (deque->max_size + 1 - deque->queue_front + deque->queue_rear) % (deque->max_size + 1);
}

bool underflow(const Deque* deque) {
    return deque->queue_front == deque->queue_rear; // inicio alcancou o fim (removeu todos)
}

void print(const Deque* deque) {
    int i = deque->queue_front;
    while (i != deque->queue_rear) {
        printf("%d ", deque->vector[i]);
        if (i == deque->max_size) { // na ultima posicao?
            i = 0;
        } else {
            ++i;
        }
    }
}
