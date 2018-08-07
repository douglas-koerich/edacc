#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

struct Noh {
    char caractere;
    struct Noh* proximo;
};

struct Pilha {
    struct Noh* topo;
};

Pilha* cria() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
}

void destroi(Pilha* p) {
    if (NULL == p) {
        return;
    }
    while (NULL != p->topo) {
        struct Noh* t = p->topo;
        p->topo = t->proximo;
        free(t);
    }
    free(p);
}

bool underflow(const Pilha* p) {
    return NULL == p || NULL == p->topo;
}

void push(Pilha* p, char c) {
    if (NULL == p) {
        return;
    }
    struct Noh* t = (struct Noh*) malloc(sizeof(struct Noh));
    t->caractere = c;
    t->proximo = p->topo;
    p->topo = t;
}

char pop(Pilha* p) {
    if (underflow(p)) {
        return -1;
    }
    struct Noh* t = p->topo;
    char c = t->caractere;
    p->topo = t->proximo;
    free(t);
    return c;
}

void print(Pilha* p) {
    if (NULL == p || NULL == p->topo) {
        printf("(empty)");
        return;
    }
    struct Noh* t = p->topo;
    while (NULL != t) {
        putchar(t->caractere);
        t = t->proximo;
    }
}
