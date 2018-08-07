#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

struct IFila {
    int* vetor;
    size_t max;
    int inicio, fim;
};

IFila* cria(size_t max) {
    IFila* nova = (IFila*) malloc(sizeof(IFila));
    nova->max = max;
    nova->vetor = (int*) malloc(sizeof(int) * nova->max);
    nova->inicio = nova->fim = nova->max-1;
    return nova;
}

void destroi(IFila* fila) {
    free(fila->vetor);
    free(fila);
}

bool underflow(const IFila* fila) {
    return fila->inicio == fila->fim;
}

bool overflow(const IFila* fila) {
    return fila->fim == (fila->inicio? fila->inicio-1: fila->max-1);
}

void enqueue(IFila* fila, int numero) {
    if (overflow(fila)) {
        return;
    }
    fila->fim = fila->fim == fila->max-1? 0: fila->fim + 1;
    fila->vetor[fila->fim] = numero;
}

int dequeue(IFila* fila) {
    if (underflow(fila)) {
        return -1;  // erro
    }
    fila->inicio = fila->inicio == fila->max-1? 0: fila->inicio + 1;
    return fila->vetor[fila->inicio];
}

void print(const IFila* fila) {
	if (underflow(fila)) {
		printf("(vazia)");
		return;
	}
    printf("(Inicio) ");
	int i = fila->inicio == fila->max-1? 0: fila->inicio + 1;
    do {
		printf("%d ", fila->vetor[i]);
        i = i == fila->max-1? 0: i + 1;
	} while (i != fila->fim);
    printf("%d ", fila->vetor[i]);  // imprime o elemento no fim
	printf("(Fim)");
}

