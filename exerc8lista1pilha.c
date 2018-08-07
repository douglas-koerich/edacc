#include <stdio.h>
#include "exerc8lista1pilha.h"

struct Pilha {
    tipo* vetor;
    size_t max;
    int topo;
};

struct Pilha* p_cria(size_t tamanho) {
    struct Pilha* p = (struct Pilha*) malloc(sizeof(struct Pilha));
    p->vetor = (tipo*) malloc(tamanho * sizeof(tipo));
    p->max = tamanho;
    p->topo = -1;
    return p;
}

void p_destroi(struct Pilha* p) {
    free(p->vetor);
    free(p);
}

bool p_underflow(const struct Pilha* p) {
    return p->topo == -1;
}

bool p_overflow(const struct Pilha* p) {
    return p->topo == p->max - 1;
}

bool push(struct Pilha* p, tipo v) {
    if (p_overflow(p)) {
        return false;
    }
    p->vetor[++p->topo] = v;
    return true;
}

bool pop(struct Pilha* p, tipo* pv) {
    if (p_underflow(p)) {
        return false;
    }
    *pv = p->vetor[p->topo--];
    return true;
}

void p_imprime(const struct Pilha* p) {
    printf("(Base) ");
    int i;
    for (i=0; i<=p->topo; ++i) {
        printf("%u ", p->vetor[i]);
    }
    printf("(Topo)\n");
}
