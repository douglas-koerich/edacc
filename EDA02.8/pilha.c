#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

struct Noh {
    int valor;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Pilha {
    Noh* topo;
};

Pilha* cria_p(void) {
    Pilha* p = malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

bool underflow_p(const Pilha* p) {
    return p->topo == NULL;
}

bool overflow_p(const Pilha* p) {
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true;
    }
    free(f);
    return false;
}

void push(Pilha *p, int i) {
    Noh* n = malloc(sizeof(Noh));
    n->valor = i;
    n->proximo = p->topo;
    p->topo = n;
}

int pop(Pilha* p) {
    Noh* n = p->topo;
    p->topo = n->proximo;
    int i = n->valor;
    free(n);
    return i;
}

void destroi_p(Pilha* p) {
    while (!underflow_p(p)) {
        Noh* n = p->topo;
        p->topo = n->proximo; 
        free(n);
    }
    free(p);
}

void imprime_p(const Pilha* p) {
    if (underflow_p(p)) {
        printf("(VAZIA)");
        return;
    }
    printf("(TOPO) ");
    Noh* n = p->topo;
    while (n != NULL) {
        printf("%d", n->valor);
        printf("-->");
        n = n->proximo;
    }
    printf("NULL (BASE)\n");
}

