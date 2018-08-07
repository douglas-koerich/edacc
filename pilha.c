#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

struct Pilha {
    generico* vetor;
    int topo;
};

#define MAX_ITENS   1000

Pilha* cria(void) {
    Pilha* p = malloc(sizeof(Pilha));
    p->vetor = malloc(sizeof(generico) * MAX_ITENS);
    p->topo = -1;
    return p;
}

void destroi(Pilha* p) {
    free(p->vetor);
    free(p);
}

bool underflow(const Pilha* p) {
    return p->topo == -1;
}

bool overflow(const Pilha* p) {
    return p->topo == MAX_ITENS-1;
}

bool push(Pilha* p, generico* i) {
    if (overflow(p)) {
        return false;
    }
    ++p->topo;
    memcpy(p->vetor + p->topo, i, sizeof(generico));
    return true;
}

generico* pop(Pilha* p) {
    if (underflow(p)) {
        return NULL;
    }
    generico* i = malloc(sizeof(generico));
    memcpy(i, p->vetor + p->topo, sizeof(generico));
    --p->topo;
    return i;
}

void imprime(const Pilha* p) {
    if (underflow(p)) {
        printf("(VAZIA)");
        return;
    }
    int i;
    printf("(BASE) ");
    for (i=0; i<=p->topo; ++i) {
        p->vetor[i].imprime(p->vetor[i].coisa);
        putchar(' ');
    }
    printf("(TOPO)"); 
}

