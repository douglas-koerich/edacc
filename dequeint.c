#include <stdlib.h>
#include <stdio.h>
#include "dequeint.h"

static const size_t MAX_ITENS = 16;

struct DequeInt {
    int* vetor;
    int esq, dir;
};

DequeInt* cria_d(void) {
    DequeInt* novo = malloc(sizeof(DequeInt));
    novo->vetor = malloc(sizeof(int) * MAX_ITENS);
    novo->esq = novo->dir = MAX_ITENS-1;
    return novo;
}

void destroi_d(DequeInt* deque) {
    free(deque->vetor);
    free(deque);
}

bool underflow_d(const DequeInt* deque) {
    return deque->esq == deque->dir;
}

bool overflow_d(const DequeInt* deque) {
    if (deque->esq == 0) {
        return deque->dir == MAX_ITENS-1;
    } else {
        return deque->dir == deque->esq - 1;
    }
}

void enqueue_d(DequeInt* deque, Extremo lado, int novo) {
    if (lado == DIREITO) {
        if (deque->dir == MAX_ITENS-1) {
            deque->dir = 0;
        } else {
            ++deque->dir;
        }
        deque->vetor[deque->dir] = novo;
    } else {
        deque->vetor[deque->esq] = novo;
        if (deque->esq == 0) {
            deque->esq = MAX_ITENS-1;
        } else {
            --deque->esq;
        }
    }
}

int dequeue_d(DequeInt* deque, Extremo lado) {
    if (lado == ESQUERDO) {
        if (deque->esq == MAX_ITENS-1) {
            deque->esq = 0;
        } else {
            ++deque->esq;
        }
        return deque->vetor[deque->esq];
    } else {
        int num = deque->vetor[deque->dir];
        if (deque->dir == 0) {
            deque->dir = MAX_ITENS-1;
        } else {
            --deque->dir;
        }
        return num;
    }
}

void print_d(const DequeInt* deque) {
    if (underflow_d(deque)) {
        return;
    }
    printf("(ESQUERDO) ");
    int indice = deque->esq == MAX_ITENS-1? 0 : deque->esq+1;
    for (;;) {
        printf("%d ", deque->vetor[indice]);
        if (indice == deque->dir) {
            break;
        }
        if (indice == MAX_ITENS-1) {
            indice = 0;
        } else {
            ++indice;
        }
    }
    printf("(DIREITO)");
}

