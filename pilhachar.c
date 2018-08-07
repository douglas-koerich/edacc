#include <stdlib.h>
#include "pilhachar.h"

static const size_t MAX_ITENS = 128;

struct PilhaChar {
    char* vetor;
    int topo;
};

PilhaChar* cria(void) {
    PilhaChar* nova = malloc(sizeof(PilhaChar));
    nova->vetor = malloc(sizeof(char) * MAX_ITENS);
    nova->topo = -1;
    return nova;
}

void destroi(PilhaChar* pilha) {
    free(pilha->vetor);
    free(pilha);
}

bool underflow(const PilhaChar* pilha) {
    return pilha->topo == -1;
}

bool overflow(const PilhaChar* pilha) {
    return pilha->topo == MAX_ITENS - 1;
}

void push(PilhaChar* pilha, char novo) {
    pilha->vetor[++pilha->topo] = novo;
}

char pop(PilhaChar* pilha) {
    return pilha->vetor[pilha->topo--];
}

