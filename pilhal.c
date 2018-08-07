#include <stdlib.h>
#include <stdio.h>
#include "pilhal.h"

// Definicao do noh da lista encadeada simples
struct NohP {
    int elemento;
    struct NohP* proximo;
};

// Definicao do TAD: Pilha na forma de lista encadeada
struct Pilha {
    struct NohP* topo;
};

struct Pilha* p_cria(void) {
    struct Pilha* l = (struct Pilha*) malloc(sizeof(struct Pilha));
    l->topo = NULL;
    return l;
}

void p_destroi(struct Pilha* l) {
    while (l->topo != NULL) {
        struct NohP* p = l->topo;
        l->topo = p->proximo;
        free(p);
    }
    free(l);
}

bool p_underflow(const struct Pilha* l) {
    return l->topo == NULL;
}

void p_imprime(const struct Pilha* l) {
    printf("(Topo)");
    struct NohP* p = l->topo;
    while (p != NULL) {
        printf("->%d", p->elemento);
        p = p->proximo;
    }
    putchar('\n');
}

bool push(struct Pilha* l, int val) {
    struct NohP* p = (struct NohP*) malloc(sizeof(struct NohP));
    if (p == NULL) {
        return false;
    }
    p->elemento = val;
    p->proximo = l->topo;
    l->topo = p;
    return true;
}

bool pop(struct Pilha* l, int* pval) {
    if (p_underflow(l)) {
        return false;
    }
    struct NohP* p = l->topo;
    l->topo = p->proximo;
    *pval = p->elemento;
    free(p);
    return true;
}

