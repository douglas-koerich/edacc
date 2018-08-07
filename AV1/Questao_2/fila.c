/* O CONTEUDO DESTE ARQUIVO //NAO// FAZIA PARTE DA QUESTAO 2, //NEM SE PODERIA
   ASSUMIR QUE A IMPLEMENTACAO DA FILA FOSSE COMO ABAIXO//. ESTA SENDO INCLUIDO
   AQUI APENAS PARA O CORRETO FUNCIONAMENTO DO PROGRAMA DEMONSTRATIVO DA SOLUCAO
   APRESENTADA */

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

#define MAX_NUM_ELEMENTOS_FILA 100

struct FilaInt {
    int* vetor;
    int inicio;
    int fim;
};

FilaInt* criar(void) {
    FilaInt* f = (FilaInt*) malloc(sizeof(struct FilaInt));
    if (f == NULL) {
        return NULL;
    }
    f->vetor = (int*) malloc(sizeof(int) * MAX_NUM_ELEMENTOS_FILA);
    if (f->vetor == NULL) {
        free(f);
        return NULL;
    }
    f->inicio = f->fim = MAX_NUM_ELEMENTOS_FILA-1;
    return f;
}

void destruir(FilaInt* f) {
    if (f == NULL) {
        return;
    }
    if (f->vetor != NULL) {
        free(f->vetor);
    }
    free(f);
}

void imprimir(const FilaInt* f) {
    if (f == NULL || f->vetor == NULL) {
        puts("(Inexistente)");
        return;
    }
    if (underflow(f)) {
        puts("(Vazia)");
        return;
    }
    printf("(inicio) ");
    int i = f->inicio;
    do {
        i = (i == MAX_NUM_ELEMENTOS_FILA-1)? 0: i + 1;
        printf("%d ", f->vetor[i]);
    } while (i != f->fim);
    printf("(fim)");
}

bool underflow(const FilaInt* f) {
    return f->inicio == f->fim;
}

bool overflow(const FilaInt* f) {
    if (f->inicio == 0) {
        return f->fim == MAX_NUM_ELEMENTOS_FILA-1;
    } else {
        return f->fim == f->inicio - 1;
    }
}

void enqueue(FilaInt* f, int n) {
    if (f->fim == MAX_NUM_ELEMENTOS_FILA-1) {
        f->fim = 0;
    } else {
        ++f->fim;
    }
    f->vetor[f->fim] = n;
}

int dequeue(FilaInt* f) {
    f->inicio = (f->inicio == MAX_NUM_ELEMENTOS_FILA-1)? 0: f->inicio + 1;
    return f->vetor[f->inicio];
}
