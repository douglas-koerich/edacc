#include <stdlib.h>
#include <stdio.h>
#include "tad_deque_inteiros.h"

#define MAX_NUM_ELEMENTOS_DEQUE 1000

struct DequeInt {
    int* vetor;
    int inicio;
    int fim;
};

DequeInt* cria_deque(void) {
    DequeInt* d = (DequeInt*) malloc(sizeof(struct DequeInt));
    if (d == NULL) {
        return NULL;
    }
    d->vetor = (int*) malloc(sizeof(int) * MAX_NUM_ELEMENTOS_DEQUE);
    if (d->vetor == NULL) {
        free(d);
        return NULL;
    }
    d->inicio = d->fim = MAX_NUM_ELEMENTOS_DEQUE-1;
    return d;
}

void destroi_deque(DequeInt* d) {
    if (d == NULL) {
        return;
    }
    if (d->vetor != NULL) {
        free(d->vetor);
    }
    free(d);
}

void imprime_deque(const DequeInt* d) {
    if (d == NULL || d->vetor == NULL) {
        puts("(Inexistente)");
        return;
    }
    if (dunderflow(d)) {
        puts("(Vazio)");
        return;
    }
    printf("(inicio) ");
    int i = d->inicio;
    do {
        i = (i == MAX_NUM_ELEMENTOS_DEQUE-1)? 0: i + 1;
        printf("%d ", d->vetor[i]);
    } while (i != d->fim);
    printf("(fim)");
}

bool dunderflow(const DequeInt* d) {
    return d->inicio == d->fim;
}

bool doverflow(const DequeInt* d) {
    // Verifica se o indice do fim estah na posicao "anterior" ao indice de inicio
    if (d->inicio == 0) {
        return d->fim == MAX_NUM_ELEMENTOS_DEQUE-1;
    } else {
        return d->fim == d->inicio - 1;
    }
}

void d_enqueue(DequeInt* d, int n, LadoDeque l) {
    if (l == FIM) { // como na fila?
        if (d->fim == MAX_NUM_ELEMENTOS_DEQUE-1) {   // testa se precisa voltar a ocupar o inicio do vetor
            d->fim = 0;
        } else {
            ++d->fim;
        }
        d->vetor[d->fim] = n;
    } else {    // como no deque apenas!
        d->vetor[d->inicio] = n;    // 'inicio' jah estah na posicao livre anterior ao primeiro
        if (d->inicio == 0) {   // volta o 'inicio' para tras
            d->inicio = MAX_NUM_ELEMENTOS_DEQUE-1;
        } else {
            --d->inicio;
        }
    }
}

int d_dequeue(DequeInt* d, LadoDeque l) {
    if (l == INICIO) {  // como na fila?
        d->inicio = (d->inicio == MAX_NUM_ELEMENTOS_DEQUE-1)? 0: d->inicio + 1;
        return d->vetor[d->inicio];
    } else {    // como no deque apenas!
        int n = d->vetor[d->fim];   // 'fim' estah no indice do ultimo inserido
        d->fim = (d->fim == 0)? MAX_NUM_ELEMENTOS_DEQUE-1: d->fim - 1;  // volta o 'fim' para tras
        return n;
    }
}
