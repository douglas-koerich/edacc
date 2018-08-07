#include <stdlib.h>
#include <stdio.h>
#include "ex2l1.h"

struct IPilha {
    int* vetor;
    size_t max;
    int topo;
};

IPilha* cria(size_t max) {
    IPilha* nova = (IPilha*) malloc(sizeof(IPilha));
    nova->max = max;
    nova->vetor = (int*) malloc(sizeof(int) * nova->max);
    nova->topo = -1;
    return nova;
}

void destroi(IPilha* pilha) {
    free(pilha->vetor);
    free(pilha);
}

bool underflow(const IPilha* pilha) {
    return pilha->topo == -1;
}

bool overflow(const IPilha* pilha) {
    return pilha->topo == pilha->max - 1;
}

void push(IPilha* pilha, int numero) {
    if (overflow(pilha)) {
        return;
    }
    pilha->vetor[++pilha->topo] = numero;
}

int pop(IPilha* pilha) {
    if (underflow(pilha)) {
        return -1;  // erro
    }
    return pilha->vetor[pilha->topo--];
}

void print(const IPilha* pilha) {
	if (underflow(pilha)) {
		printf("(vazia)");
		return;
	}
	int i;
	for (i=0; i<=pilha->topo; ++i) {
		printf("%d ", pilha->vetor[i]);
	}
	printf("(Topo)");
}

