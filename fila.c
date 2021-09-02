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
                                                 // deve-se ter sempre uma 
                                                 // posicao livre no vetor
    nova->tamanho = max;
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

static bool overflow(const fila* f) { // teste de fila cheia
    return (f == NULL) ||
           (f->inicio == 0 && f->fim == f->tamanho) ||
           (f->inicio > 0 && f->fim == f->inicio - 1);
}

void insert(fila* f, int v) {
    if (overflow(f) == true) {
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
    int n = f->fim - f->inicio;
    if (n < 0) { // 'fim' antes de 'inicio' no vetor?
        n += f->tamanho + 1;
    }
    return n;
}

bool underflow(const fila* f) {
    return f == NULL || f->inicio == f->fim;
}

void print(const fila* f) {
    if (f == NULL) {
        return;
    }
    if (underflow(f)) {
        puts("(VAZIA)");
        return;
    }
    int i = f->inicio;
    while (i != f->fim) {
        printf("%d ", f->vetor[i]);
        if (++i == f->tamanho + 1) {
            i = 0;
        }
    }
}

void save(const fila* f, const char* a) {
    if (f == NULL || a == NULL) {
        return;
    }
    FILE* s = fopen(a, "wb");
    if (s == NULL) {
        perror("Nao foi possivel criar o arquivo da fila");
        return;
    }
    int i = f->inicio;
    while (i != f->fim) {
        fwrite(&f->vetor[i], sizeof(int), 1, s);
        if (++i == f->tamanho) {
            i = 0;
        }
    }
    fclose(s);
}

fila* restore(const char* a) {
    if (a == NULL) {
        return NULL;
    }
    FILE* s = fopen(a, "rb");
    if (s == NULL) {
        perror("Nao foi possivel abrir o arquivo da fila");
        return NULL;
    }
    const int MAX_FILA = 1000;
    fila* nova = create(MAX_FILA);
    while (!feof(s)) {
        int num;
        if (fread(&num, sizeof(int), 1, s) < 1) {
            if (ferror(s)) {
                perror("Erro na leitura do arquivo");
                return NULL;
            }
        } else {
            insert(nova, num);
        }
    }
    fclose(s);

    return nova;
}
