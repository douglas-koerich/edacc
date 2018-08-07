#include <stdlib.h>
#include <stdio.h> // para uso em imprime()
#include "filaint.h"

static const size_t MAX_ITENS = 16;

struct FilaInt {
    int* vetor;
    int inicio, fim;
};

FilaInt* cria(void) {
    FilaInt* nova = malloc(sizeof(FilaInt));
    nova->vetor = malloc(sizeof(int) * MAX_ITENS);
    /* Fila linear
    nova->inicio = nova->fim = -1;
    */
    // Fila circular
    nova->inicio = nova->fim = MAX_ITENS-1;
    return nova;
}

void destroi(FilaInt* fila) {
    free(fila->vetor);
    free(fila);
}

bool underflow(const FilaInt* fila) {
    return fila->inicio == fila->fim;
}

bool overflow(const FilaInt* fila) {
    /* Fila linear
    return fila->fim == MAX_ITENS - 1;
    */
    // Fila circular: fim NAO PODE alcancar o inicio
    if (fila->inicio == 0) {
        return fila->fim == MAX_ITENS-1;
    } else {
        return fila->fim == fila->inicio - 1;
    }
}

void enqueue(FilaInt* fila, int novo) {
    /* Fila linear
    fila->vetor[++fila->fim] = novo;
    */
    // Fila circular
    if (fila->fim == MAX_ITENS-1) {
        fila->fim = 0;
    } else {
        ++fila->fim;
    }
    fila->vetor[fila->fim] = novo;
}

int dequeue(FilaInt* fila) {
    /* Fila linear
    return fila->vetor[++fila->inicio];
    */
    // Fila circular
    if (fila->inicio == MAX_ITENS-1) {
        fila->inicio = 0;
    } else {
        ++fila->inicio;
    }
    return fila->vetor[fila->inicio];
}

void print(const FilaInt* fila) {
    if (underflow(fila)) {
        printf("\n(VAZIA)\n");
        return;
    }
    printf("\n(INICIO) ");
    int indice = fila->inicio == MAX_ITENS-1? 0 : fila->inicio+1;
    for (;;) {
        printf("%d ", fila->vetor[indice]);
        if (indice == fila->fim) {
            break;
        }
        if (indice == MAX_ITENS-1) {
            indice = 0;
        } else {
            ++indice;
        }
    }
    printf("(FIM)\n");
}

