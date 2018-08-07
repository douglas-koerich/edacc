#include <stdlib.h>
#include <stdio.h>
#include "pilhaint_p.h"

PilhaInt* cria_p(void) {
    return (PilhaInt*) cria_d();
}

void destroi_p(PilhaInt* pilha) {
    destroi_d((DequeInt*) pilha);
}

bool underflow_p(const PilhaInt* pilha) {
    return underflow_d((const DequeInt*) pilha);
}

bool overflow_p(const PilhaInt* pilha) {
    return overflow_d((const DequeInt*) pilha);
}

void push(PilhaInt* pilha, int novo) {
    enqueue_d((DequeInt*) pilha, DIREITO, novo);
}

int pop(PilhaInt* pilha) {
    return dequeue_d((DequeInt*) pilha, DIREITO);
}

void print_p(const PilhaInt* pilha) {
    printf("(BASE) ");
    print_d((const DequeInt*) pilha);
    printf(" (TOPO)");
}

