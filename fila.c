#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

// Definicao interna da estrutura, ou seja, sua
// implementacao (neste caso, circular usando contiguidade fisica,
// i.e., um vetor como repositorio da fila)
static const size_t MAX_FILA = 1000; // depende do uso/proposito
struct FilaT {
    T* vetor;
    int inicio, fim;
};

FilaT* cria(void) {
    FilaT* nova = malloc(sizeof(FilaT));
    nova->vetor = malloc(sizeof(T) * MAX_FILA);
    nova->inicio = nova->fim = MAX_FILA-1;
    return nova;
}

void destroi(FilaT* fila) {
    free(fila->vetor);
    free(fila);
}

void imprime(const FilaT* fila) {
    if (underflow(fila)) {
        printf("(VAZIA)");
        return;
    }
    printf("INICIO> ");
    int i = fila->inicio == MAX_FILA-1? 0: fila->inicio+1;
    while (true) {
        printf("%t ", fila->vetor[i]);
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

bool underflow(const FilaT* fila) {
    return fila->inicio == fila->fim;
}

bool overflow(const FilaT* fila) {
    if (fila->inicio == 0) {
        return fila->fim == MAX_FILA-1;
    }
    return fila->fim == fila->inicio-1;
}

void enqueue(FilaT* fila, T valor) {
    if (fila->fim == MAX_FILA-1) {
        fila->fim = -1;
    }
    fila->vetor[++fila->fim] = valor;
}

T dequeue(FilaT* fila) {
    if (fila->inicio == MAX_FILA-1) {
        fila->inicio = -1;
    }
    return fila->vetor[++fila->inicio];
}

