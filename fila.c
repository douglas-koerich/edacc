#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fila.h"

struct fila {
    int* vetor;
    size_t tamanho;

    int inicio, fim;
};

fila* create(size_t max) {
    fila* nova = malloc(sizeof(fila));
    nova->vetor = malloc((max+1) * sizeof(int)); // uma posicao extra porque
    nova->tamanho = max+1;                       // deve-se ter sempre uma posicao
                                                 // livre no vetor

    nova->fim = 0;
    nova->inicio = 0; // apesar de nao haver um elemento neste indice pra ser
                      // removido, essa igualdade com o indice 'fim' eh que vai
                      // indicar que a fila estah de fato vazia

    return nova;
}

void destroy(fila* f) {
    if (f == NULL) {
        return;
    }
    free(f->vetor);
    free(f);
}

void insert(fila* f, int v) {
    if (f == NULL ||
        (f->inicio == 0 && f->fim == f->tamanho) ||  // testes de fila cheia
        (f->inicio > 0 && f->fim == f->inicio - 1)) {
        return;
    }
    f->vetor[f->fim] = v;
    if (f->fim == f->tamanho) { // chegou no ultimo indice do vetor?
        f->fim = 0;
    } else {
        ++f->fim;
    }
}

int extract(fila* f) {
    if (underflow(f)) {
        return INT_MIN;
    }
    int v = f->vetor[f->inicio];
    if (f->inicio == f->tamanho) {
        f->inicio = 0;
    } else {
        ++f->inicio;
    }
    return v;
}

int inspect(const fila* f) {
    if (underflow(f)) {
        return INT_MIN;
    }
    return f->vetor[f->inicio];
}

size_t size(const fila* f) {

}

bool underflow(const fila* f) {
    return f == NULL || f->inicio == f->fim;
}

void print(const fila* f) {

}

void save(const fila* f, const char* a) {

}

void restore(fila* f, const char* a) {

}
