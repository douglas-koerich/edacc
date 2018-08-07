#include <stdlib.h>
#include "pilha_ch.h"

#define MAX 100

// Definicao da estrutura
struct PilhaCh {
    char vetor[MAX];
    int topo;
};

// Implementacao das operacoes
struct PilhaCh* cria(void) {
    struct PilhaCh* p = (struct PilhaCh*) malloc(sizeof(struct PilhaCh));
    p->topo = -1;   // pilha vazia
    return p;
}

void destroi(struct PilhaCh* p) {
    free(p);
}

bool underflow(const struct PilhaCh* p) {
    return p->topo == -1;
}

bool overflow(const struct PilhaCh* p) {
    return p->topo == MAX-1;
}

bool push(struct PilhaCh* p, char c) {
    if (overflow(p)) {
        return false;
    }
    p->vetor[++p->topo] = c;
    return true;
}

bool pop(struct PilhaCh* p, char* pc) {
    if (underflow(p)) {
        return false;
    }
    *pc = p->vetor[p->topo--];
    return true;
}

