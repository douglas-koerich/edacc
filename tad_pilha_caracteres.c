#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha_caracteres.h"

#define MAX_NUM_ELEMENTOS_PILHA 100

struct PilhaChar {
    char* vetor;
    int topo;
};

PilhaChar* cria_pilha(void) {
    PilhaChar* p = (PilhaChar*) malloc(sizeof(struct PilhaChar));
    if (p == NULL) {
        return NULL;
    }
    p->vetor = (char*) malloc(sizeof(char) * MAX_NUM_ELEMENTOS_PILHA);
    if (p->vetor == NULL) {
        free(p);
        return NULL;
    }
    p->topo = -1;
    return p;
}

void destroi_pilha(PilhaChar* p) {
    if (p == NULL) {
        return;
    }
    if (p->vetor != NULL) {
        free(p->vetor);
    }
    free(p);
}

void imprime_pilha(const PilhaChar* p) {
    if (p == NULL || p->vetor == NULL) {
        puts("(Inexistente)");
        return;
    }
    if (underflow(p)) {
        puts("(Vazia)");
        return;
    }
    puts("|top|");
    int i = p->topo;
    while (i >= 0) {
        printf("| %c |\n", p->vetor[i]);
        --i;
    }
    puts("+---+");
}

bool underflow(const PilhaChar* p) {
    return p->topo == -1;
}

bool overflow(const PilhaChar* p) {
    return p->topo == MAX_NUM_ELEMENTOS_PILHA-1;
}

void push(PilhaChar* p, char ch) {
    p->vetor[++p->topo] = ch;
}

char pop(PilhaChar* p) {
    return p->vetor[p->topo--];
}
