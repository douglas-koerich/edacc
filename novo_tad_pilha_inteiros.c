#include <stdlib.h>
#include <stdio.h>
#include "novo_tad_pilha_inteiros.h"

struct Noh {
    int elemento;
    struct Noh* proximo;    // link para o seguinte na pilha
};
typedef struct Noh Noh;

struct PilhaInt {
    Noh* topo;    // endereco do primeiro noh
};

PilhaInt* cria(void) {
    PilhaInt* p = (PilhaInt*) malloc(sizeof(PilhaInt));
    p->topo = NULL;   // pilha vazia
    return p;
}

void destroi(PilhaInt* p) {
    if (p == NULL) {
        return;
    }
    while (!punderflow(p)) {
        pop(p);
    }
    free(p);
}

bool punderflow(const PilhaInt* p) {
    return p == NULL || p->topo == NULL;
}

void push(PilhaInt* p, int n) {
    if (p == NULL) {
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    noh->proximo = p->topo;
    p->topo = noh;
}

int pop(PilhaInt* p) {
    if (punderflow(p)) {
        return 0;
    }
    Noh* x = p->topo;
    p->topo = x->proximo;
    int n = x->elemento;
    free(x);
    return n;
}
