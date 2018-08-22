#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

static const size_t MAX_PILHA = 1000; // valor razoavel para o problema
struct Pilha {
    char* vetor;
    int topo;
};

Pilha* cria(void) {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->vetor = malloc(sizeof(char) * MAX_PILHA);
    nova->topo = -1;
    return nova;
}

void destroi(Pilha* pilha) {
    free(pilha->vetor);
    free(pilha);
}

void imprime(const Pilha* pilha) {
    if (underflow(pilha)) {
        printf("(VAZIA)");
        return;
    }
    printf("BASE> ");
    int i;
    for (i=0; i<=pilha->topo; ++i) {
        printf("%c ", pilha->vetor[i]);
    }
    printf("<TOPO");
}

bool underflow(const Pilha* pilha) {
    return pilha->topo == -1;
}

bool overflow(const Pilha* pilha) {
    return pilha->topo == MAX_PILHA-1;
}

void push(Pilha* pilha, char valor) {
    pilha->vetor[++pilha->topo] = valor;
}

char pop(Pilha* pilha) {
    return pilha->vetor[pilha->topo--];
}

