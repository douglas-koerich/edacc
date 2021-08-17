#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "pilha.h"

struct pilha {
    int* vetor; // alocado dinamicamente para conter a pilha
    size_t tamanho;

    int topo; // indice (posicao no vetor) do elemento que pode ser acessado
};

pilha* create(size_t max) {
    pilha* nova = malloc(sizeof(pilha));
    nova->tamanho = max;

    nova->vetor = malloc(sizeof(int) * max);

    nova->topo = -1; // indice invalido, pois a pilha ainda nao estah sendo usada (nao existe elemento na posicao 0, por exemplo)

    return nova;
}

void destroy(pilha* p) {
    if (p == NULL) {
        return;
    }
    free(p->vetor);
    free(p);
}

void push(pilha* p, int v) {
    if (p == NULL) {
        return;
    }
    p->vetor[++p->topo] = v; // incrementa 'topo' antes de armazenar novo valor
}

int pop(pilha* p) {
    if (underflow(p)) {
        return INT_MIN;
    }
    return p->vetor[p->topo--]; // decrementa 'topo' apos uso como indice do vetor
}

int top(const pilha* p) {
    if (underflow(p)) {
        return INT_MIN;
    }
    return p->vetor[p->topo];
}

size_t size(const pilha* p) {
    if (p == NULL) {
        return 0;
    }
    return p->topo + 1;
}

bool underflow(const pilha* p) {
    if (p == NULL) {
        return true;
    }
    return p->topo == -1;
}

void print(const pilha* p) {
    if (p == NULL) {
        return;
    }
    if (underflow(p)) {
        puts("(VAZIA)");
        return;
    }
    int i = p->topo;
    while (i >= 0) {
        printf("| %2d |\n", p->vetor[i]);
        --i;
    }
    printf("+----+");
}
