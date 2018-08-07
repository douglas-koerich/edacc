#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha_inteiros.h"

#define MAX_NUM_ELEMENTOS_PILHA 100

// Definicao oculta da estrutura de dados na memoria
struct PilhaInt {
    int* vetor; // vetor alocado dinamicamente
    int topo;   // indice do topo ("memoria do ultimo adicionado")
};

PilhaInt* cria_pilha(void) {
    PilhaInt* p = (PilhaInt*) malloc(sizeof(struct PilhaInt));
    if (p == NULL) {
        return NULL;
    }
    p->vetor = (int*) malloc(sizeof(int) * MAX_NUM_ELEMENTOS_PILHA);
    if (p->vetor == NULL) {
        free(p);    // ja aloquei, tenho que liberar
        return NULL;
    }
    p->topo = -1;   // topo eh o indice da ultima posicao ocupada (nenhuma)
    return p;
}

void destroi_pilha(PilhaInt* p) {
    if (p == NULL) {
        return;
    }
    if (p->vetor != NULL) {
        free(p->vetor);
    }
    free(p);
}

void imprime_pilha(const PilhaInt* p) {
    if (p == NULL || p->vetor == NULL) {
        puts("(Inexistente)");
        return;
    }
    if (punderflow(p)) {
        puts("(Vazia)");
        return;
    }
    puts("| (Topo) |");
    int i = p->topo;
    while (i >= 0) {
        printf("| %6d |\n", p->vetor[i]);
        --i;
    }
    puts("+--------+");
}

bool punderflow(const PilhaInt* p) {
    return p->topo == -1;
}

bool poverflow(const PilhaInt* p) {
    return p->topo == MAX_NUM_ELEMENTOS_PILHA-1;
}

void push(PilhaInt* p, int num) {
    /*
    ++p->topo;  // ir para a posicao seguinte (primeira livre)
    p->vetor[p->topo] = num;
    */
    p->vetor[++p->topo] = num;  // incrementa antes de indexar
}

int pop(PilhaInt* p) {
    /*
    int num = p->vetor[p->topo];
    --p->topo;
    return num;
    */
    return p->vetor[p->topo--];
}
