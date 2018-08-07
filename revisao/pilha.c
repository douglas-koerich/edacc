#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

struct IPilha {
    int* vetor;
    size_t max;
    int topo;
};

IPilha* p_cria(size_t max) {
    IPilha* nova = (IPilha*) malloc(sizeof(IPilha));
    nova->max = max;
    nova->vetor = (int*) malloc(sizeof(int) * nova->max);
    nova->topo = -1;
    return nova;
}

void p_destroi(IPilha* pilha) {
    free(pilha->vetor);
    free(pilha);
}

bool p_underflow(const IPilha* pilha) {
    return pilha->topo == -1;
}

bool p_overflow(const IPilha* pilha) {
    return pilha->topo == pilha->max - 1;
}

void push(IPilha* pilha, int numero) {
    if (p_overflow(pilha)) {
        return;
    }
    pilha->vetor[++pilha->topo] = numero;
}

int pop(IPilha* pilha) {
    if (p_underflow(pilha)) {
        return -1;  // erro
    }
    return pilha->vetor[pilha->topo--];
}

void p_print(const IPilha* pilha) {
	if (p_underflow(pilha)) {
		printf("(vazia)");
		return;
	}
	int i;
	for (i=0; i<=pilha->topo; ++i) {
		printf("%d ", pilha->vetor[i]);
	}
	printf("(Topo)");
}

