#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

struct IDeque {
    int vetor[MAX_ELEMENTOS+1]; // +1 para a posicao sacrificada no vetor quando o deque estah cheio
    int esq, dir;
};

IDeque* cria() {
    IDeque* nova = (IDeque*) malloc(sizeof(IDeque));
    nova->esq = nova->dir = MAX_ELEMENTOS;
    return nova;
}

void destroi(IDeque* deque) {
    free(deque);
}

bool underflow(const IDeque* deque) {
    return deque->esq == deque->dir;
}

bool overflow(const IDeque* deque) {
    return deque->dir == (deque->esq? deque->esq-1: MAX_ELEMENTOS);
}

void insere(IDeque* deque, int numero, Lado lado) {
    if (lado == DIR) {
        deque->dir = deque->dir == MAX_ELEMENTOS? 0: deque->dir + 1;
        deque->vetor[deque->dir] = numero;
    }
    else {
        deque->vetor[deque->esq] = numero;
        deque->esq = deque->esq == 0? MAX_ELEMENTOS: deque->esq - 1;
    }
}

int remove_(IDeque* deque, Lado lado) {
    if (underflow(deque)) {
        return -1;  // erro
    }
    if (lado == ESQ) {
        deque->esq = deque->esq == MAX_ELEMENTOS? 0: deque->esq + 1;
        return deque->vetor[deque->esq];
    }
    else {
        int i = deque->vetor[deque->dir];
        deque->dir = deque->dir == 0? MAX_ELEMENTOS: deque->dir - 1;
        return i;
    }
}

void print(const IDeque* deque) {
	if (underflow(deque)) {
		printf("(vazio)");
		return;
	}
    printf("(Esquerda) ");
	int i = deque->esq == MAX_ELEMENTOS? 0: deque->esq + 1;
    do {
		printf("%d ", deque->vetor[i]);
        i = i == MAX_ELEMENTOS? 0: i + 1;
	} while (i != deque->dir);
    printf("%d ", deque->vetor[i]);
	printf("(Direita)");
}
