#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

static const size_t MAX_DEQUE = 1000; // depende do uso/proposito
struct Deque {
    int* vetor;
    int frente, tras;
};

Deque* cria(void) {
    Deque* nova = malloc(sizeof(Deque));
    nova->vetor = malloc(sizeof(int) * MAX_DEQUE);
    nova->frente = nova->tras = MAX_DEQUE-1;
    return nova;
}

void destroi(Deque* deque) {
    free(deque->vetor);
    free(deque);
}

void imprime(const Deque* deque) {
    if (underflow(deque)) {
        printf("(VAZIO)");
        return;
    }
    printf("FRENTE> ");
    int i = deque->frente == MAX_DEQUE-1? 0: deque->frente+1;
    while (true) {
        printf("%d ", deque->vetor[i]);
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

bool underflow(const Deque* deque) {
    return deque->frente == deque->tras;
}

bool overflow(const Deque* deque) {
    if (deque->frente == 0) {
        return deque->tras == MAX_DEQUE-1;
    }
    return deque->tras == deque->frente-1;
}

void enqueue(Deque* deque, int valor, Extremo lado) {
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

int dequeue(Deque* deque, Extremo lado) {
    if (lado == FRENTE) {
        if (deque->frente == MAX_DEQUE-1) {
            deque->frente = -1;
        }
        return deque->vetor[++deque->frente];
    } else {
        int aux = deque->vetor[deque->tras];
        if (deque->tras == 0) {
            deque->tras = MAX_DEQUE-1;
        } else {
            --deque->tras;
        }
        return aux;
    }
}

