#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

// Definicao interna da estrutura, ou seja, sua
// implementacao (neste caso, usando contiguidade fisica,
// i.e., um vetor como repositorio da pilha)
static const size_t MAX_PILHA = 1000; // depende do uso/proposito
struct PilhaT {
    T* vetor;
    int topo;
};

PilhaT* cria(void) {
    PilhaT* nova = malloc(sizeof(PilhaT));
    nova->vetor = malloc(sizeof(T) * MAX_PILHA);
    nova->topo = -1;
    return nova;
}

void destroi(PilhaT* pilha) {
    free(pilha->vetor);
    free(pilha);
}

void imprime(const PilhaT* pilha) {
    if (underflow(pilha)) {
        printf("(VAZIA)");
        return;
    }
    printf("BASE> ");
    int i;
    for (i=0; i<=pilha->topo; ++i) {
        printf("%t ", pilha->vetor[i]);
    }
    printf("<TOPO");
}

bool underflow(const PilhaT* pilha) {
    return pilha->topo == -1;
}

bool overflow(const PilhaT* pilha) {
    return pilha->topo == MAX_PILHA-1;
}

void push(PilhaT* pilha, T valor) {
    pilha->vetor[++pilha->topo] = valor;
}

T pop(PilhaT* pilha) {
    return pilha->vetor[pilha->topo--];
}

