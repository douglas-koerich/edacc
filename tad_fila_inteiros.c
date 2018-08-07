#include <stdlib.h>
#include <stdio.h>
#include "tad_fila_inteiros.h"

#define MAX_NUM_ELEMENTOS_FILA 100

struct FilaInt {
    int* vetor;
    int inicio;
    int fim;
};

FilaInt* cria_fila(void) {
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

void destroi_fila(FilaInt* f) {
    if (f == NULL) {
        return;
    }
    if (f->vetor != NULL) {
        free(f->vetor);
    }
    free(f);
}

void imprime_fila(const FilaInt* f) {
    if (f == NULL || f->vetor == NULL) {
        puts("(Inexistente)");
        return;
    }
    if (funderflow(f)) {
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

bool funderflow(const FilaInt* f) {
    return f->inicio == f->fim;
}

bool foverflow(const FilaInt* f) {
    // Verifica se o indice do fim estah na posicao "anterior" ao indice de inicio
    if (f->inicio == 0) {
        return f->fim == MAX_NUM_ELEMENTOS_FILA-1;
    } else {
        return f->fim == f->inicio - 1;
    }
}

void enqueue(FilaInt* f, int n) {
    if (f->fim == MAX_NUM_ELEMENTOS_FILA-1) {   // testa se precisa voltar a ocupar o inicio do vetor
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

#include "tad_pilha_inteiros.h"

void inverte(FilaInt* f) {
    PilhaInt* p = cria_pilha();
    while (!funderflow(f)) {
        push(p, dequeue(f));
    }
    while (!punderflow(p)) {
        enqueue(f, pop(p));
    }
    destroi_pilha(p);
}
