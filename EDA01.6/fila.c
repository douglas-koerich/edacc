#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

static const size_t MAX_FILA = 5; // depende do uso/proposito
struct Fila {
    int* vetor;
    int inicio, fim;
};

Fila* cria(void) {
    Fila* nova = malloc(sizeof(Fila));
    nova->vetor = malloc(sizeof(int) * MAX_FILA);
    nova->inicio = nova->fim = MAX_FILA-1;
    return nova;
}

void destroi(Fila* fila) {
    free(fila->vetor);
    free(fila);
}

void imprime(const Fila* fila) {
    if (underflow(fila)) {
        printf("(VAZIA)");
        return;
    }
    printf("INICIO> ");
    int i = fila->inicio == MAX_FILA-1? 0: fila->inicio+1;
    while (true) {
        printf("%d ", fila->vetor[i]);
        if (i == fila->fim) {
            break;
        }
        if (i == MAX_FILA-1) {
            i = 0;
        } else {
            ++i;
        }
    } 
    printf("<FIM");
}

bool underflow(const Fila* fila) {
    return fila->inicio == fila->fim;
}

bool overflow(const Fila* fila) {
    if (fila->inicio == 0) {
        return fila->fim == MAX_FILA-1;
    }
    return fila->fim == fila->inicio-1;
}

void enqueue(Fila* fila, int valor) {
    if (fila->fim == MAX_FILA-1) {
        fila->fim = -1;
    }
    fila->vetor[++fila->fim] = valor;
}

int dequeue(Fila* fila) {
    if (fila->inicio == MAX_FILA-1) {
        fila->inicio = -1;
    }
    return fila->vetor[++fila->inicio];
}

size_t tamanho(const Fila* fila) {
    if (fila->fim >= fila->inicio) {
        return fila->fim - fila->inicio;
    }
    return fila->fim + MAX_FILA - fila->inicio;
}

