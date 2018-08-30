#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

// Definicao interna da estrutura, ou seja, sua
// implementacao (neste caso, circular usando contiguidade fisica,
// i.e., um vetor como repositorio do deque)
static const size_t MAX_DEQUE = 1000; // depende do uso/proposito
struct DequeT {
    T* vetor;
    int frente, tras;
};

DequeT* cria(void) {
    DequeT* nova = malloc(sizeof(DequeT));
    nova->vetor = malloc(sizeof(T) * MAX_DEQUE);
    nova->frente = nova->tras = MAX_DEQUE-1;
    return nova;
}

void destroi(DequeT* deque) {
    free(deque->vetor);
    free(deque);
}

void imprime(const DequeT* deque) {
    if (underflow(deque)) {
        printf("(VAZIA)");
        return;
    }
    printf("FRENTE> ");
    int i = deque->frente == MAX_DEQUE-1? 0: deque->frente+1;
    while (true) {
        printf("%t ", deque->vetor[i]);
        if (i == deque->tras) {
            break;
        }
        if (i == MAX_DEQUE-1) {
            i = 0;
        } else {
            ++i;
        }
    } 
    printf("<TRAS");
}

bool underflow(const DequeT* deque) {
    return deque->frente == deque->tras;
}

bool overflow(const DequeT* deque) {
    if (deque->frente == 0) {
        return deque->tras == MAX_DEQUE-1;
    }
    return deque->tras == deque->frente-1;
}

void enqueue(DequeT* deque, T valor, Extremo lado) {
    if (lado == TRAS) {
        if (deque->tras == MAX_DEQUE-1) {
            deque->tras = -1;
        }
        deque->vetor[++deque->tras] = valor;
    } else {
        deque->vetor[deque->frente] = valor;
        if (deque->frente == 0) {
            deque->frente = MAX_DEQUE-1;
        } else {
            --deque->frente;
        }
    }
}

T dequeue(DequeT* deque, Extremo lado) {
    if (lado == FRENTE) {
        if (deque->frente == MAX_DEQUE-1) {
            deque->frente = -1;
        }
        return deque->vetor[++deque->frente];
    } else {
        T aux = deque->vetor[deque->tras];
        if (deque->tras == 0) {
            deque->tras = MAX_DEQUE-1;
        } else {
            --deque->tras;
        }
        return aux;
    }
}

