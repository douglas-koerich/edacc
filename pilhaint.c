#include <stdlib.h>
#include "pilhaint.h"

static const size_t MAX_ITENS = 128;

struct PilhaInt {
    int* vetor;
    int topo;
};

PilhaInt* cria(void) {
    PilhaInt* nova = malloc(sizeof(PilhaInt));
    nova->vetor = malloc(sizeof(int) * MAX_ITENS);
    nova->topo = -1;
    return nova;
}

void destroi(PilhaInt* pilha) {
    free(pilha->vetor);
    free(pilha);
}

bool underflow(const PilhaInt* pilha) {
    return pilha->topo == -1;
}

bool overflow(const PilhaInt* pilha) {
    return pilha->topo == MAX_ITENS - 1;
}

void push(PilhaInt* pilha, int novo) {
    pilha->vetor[++pilha->topo] = novo;
}

int pop(PilhaInt* pilha) {
    return pilha->vetor[pilha->topo--];
}

