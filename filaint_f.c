#include <stdlib.h>
#include <stdio.h>
#include "filaint_f.h"

FilaInt* cria_f(void) {
    return (FilaInt*) cria_d();
}

void destroi_f(FilaInt* fila) {
    destroi_d((DequeInt*) fila);
}

bool underflow_f(const FilaInt* fila) {
    return underflow_d((const DequeInt*) fila);
}

bool overflow_f(const FilaInt* fila) {
    return overflow_d((const DequeInt*) fila);
}

void enqueue_f(FilaInt* fila, int novo) {
    enqueue_d((DequeInt*) fila, DIREITO, novo);
}

int dequeue_f(FilaInt* fila) {
    return dequeue_d((DequeInt*) fila, ESQUERDO);
}

void print_f(const FilaInt* fila) {
    printf("(INICIO) ");
    print_d((const DequeInt*) fila);
    printf(" (FIM)");
}

