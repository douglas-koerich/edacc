#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

#define TAM_DEQUE 1024

struct Deque {
    char* vetor; // vetor alocado dinamicamente
    int inicio;  // indice de referencia para remocao
    int fim;     // indice de referencia para insercao
};

Deque* cria_d(void) {
    Deque* f = malloc(sizeof(Deque));
    f->vetor = malloc(sizeof(char) * TAM_DEQUE);
    f->inicio = f->fim = TAM_DEQUE-1; // ultimo indice
    return f;
}

void destroi_d(Deque* f) {
    if (f == NULL) {
        return;
    }
    free(f->vetor);
    free(f);
}

bool underflow_d(const Deque* f) {
    if (f == NULL) {
        return false;
    }
    return f->inicio == f->fim;
}

bool overflow_d(const Deque* f) {
    if (f == NULL) {
        return false;
    }
    if (f->inicio == 0) {
        return f->fim == TAM_DEQUE - 1;
    }
    return f->fim == f->inicio - 1;
}

bool enqueue_d(Deque* f, char c, Extremidade e) {
    if (overflow_d(f)) {
        return false;
    }
    if (e == FIM) { // caso classico da fila
        if (f->fim == TAM_DEQUE - 1) {
            f->fim = 0;
        } else {
            ++f->fim;
        }
        f->vetor[f->fim] = c;
    } else { // caso novo do deque
        // O indice 'inicio' estah posicionado ANTES do primeiro elemento da
        // fila, portanto numa posicao livre
        f->vetor[f->inicio] = c;
        if (f->inicio == 0) {
            f->inicio = TAM_DEQUE - 1;
        } else {
            --f->inicio;
        }
    }
    return true;
}

bool dequeue_d(Deque* f, char* pc, Extremidade e) {
    if (underflow_d(f)) {
        return false;
    }
    if (pc == NULL) {
        return false;
    }
    if (e == INICIO) { // caso classico da fila
        if (f->inicio == TAM_DEQUE - 1) {
            f->inicio = 0;
        } else {
            ++f->inicio;
        }
        *pc = f->vetor[f->inicio];
    } else { // caso novo do deque
        // O indice 'fim' estah posicionado SOBRE o ultimo elemento da
        // fila, portanto naquele que serah removido
        *pc = f->vetor[f->fim];
        if (f->fim == 0) {
            f->fim = TAM_DEQUE - 1;
        } else {
            --f->fim;
        }
    }
    return true;
}

#ifdef DEBUG
void imprime_d(const Deque* f) {
    if (f == NULL) {
        return;
    }
    printf("\nINICIO >> [");
    if (underflow_d(f)) {
        printf("**vazio**");
    } else {
        int i = f->inicio;
        do {
            i = i==TAM_DEQUE-1? 0: i+1;
            putchar(f->vetor[i]);
            if (i != f->fim) {
                putchar(' ');
            }
        } while (i != f->fim);
    }
    printf("] << FIM\n");
}
#endif

