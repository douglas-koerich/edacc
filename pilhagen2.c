#include <stdio.h>
#include <string.h> // declaracao de memcpy
#include "pilhagen.h"
#include "dequegen.h"

// Definicao do TAD pilha em funcao do TAD deque
struct pilha {
    Deque* impl;
};

Pilha* cria(size_t tamanho) {
    Pilha* p = malloc(sizeof(struct pilha));
    p->impl = cria_d(tamanho);
    return p;
}

bool underflow(const Pilha* p) {
    return underflow_d(p->impl);
}

bool overflow(const Pilha* p) {
    return overflow_d(p->impl);
}

void destroi(Pilha* p) {
    destroi_d(p->impl);
    free(p);
}

void dump(const Pilha* p) {
    printf("(BASE) ");
    dump_d(p->impl);
    printf("(TOPO)");
}

void push(Pilha* p, const Tipo* v) {
    if (overflow(p)) {
        fprintf(stderr, "Pilha cheia!\n");
        return;
    }
    enqueue_d(p->impl, v, FIM);
}

void pop(Pilha* p, Tipo* v) {
    if (underflow(p)) {
        fprintf(stderr, "Pilha vazia, IGNORE *v!\n");
        return;
    }
    dequeue_d(p->impl, v, FIM);
}

