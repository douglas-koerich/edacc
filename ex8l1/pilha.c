#include "pilha.h"
#include <stdlib.h>

#define TAM_PILHA   1024

struct Pilha {
    char* vetor;
    int topo;
};

Pilha* cria_p(void) {
    Pilha* p = malloc(sizeof(Pilha));
    p->vetor = malloc(sizeof(char) * TAM_PILHA);
    p->topo = -1;
    return p;
}

void destroi_p(Pilha* p) {
    if (p == NULL) {
        return;
    }
    free(p->vetor);
    free(p);
}

bool underflow_p(const Pilha* p) {
    if (p == NULL) {
        return false;
    }
    return p->topo == -1;
}

static bool overflow_p(const Pilha* p) { // static marca uma funcao privada
                                         // neste modulo/arquivo-fonte em C
    if (p == NULL) {
        return false;
    }
    return p->topo == TAM_PILHA - 1;
}

bool push(Pilha* p, char c) {
    if (overflow_p(p)) {
        return false;
    }
    p->vetor[++p->topo] = c;
    return true;
}

bool pop(Pilha* p, char* pc) {
    if (underflow_p(p)) {
        return false;
    }
    if (pc == NULL) {
        return false;
    }
    *pc = p->vetor[p->topo--];
    return true;
}

