#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "hash.h"

struct hash {
    item* vetor;
    size_t tamanho;
};

hash* create(size_t tamanho) {
    hash* nova = malloc(sizeof(hash));
    nova->vetor = calloc(tamanho, sizeof(item)); // inicializa area com 0s
    nova->tamanho = tamanho;
    return nova;
}

void destroy(hash* tabela) {
    free(tabela->vetor);
    free(tabela);
}

static int hashing(const hash* tabela, int chave) {
    int indice = chave % tabela->tamanho;
    printf("chave = %d, indice = %d\n", chave, indice);
    return indice;
}

item* search(const hash* tabela, int chave) {
    int onde = hashing(tabela, chave);
    if (tabela->vetor[onde].chave == chave) { // registro estah la?
        return &tabela->vetor[onde];
    }
    return NULL;
}

void insert(hash* tabela, const item* registro) {
    int onde = hashing(tabela, registro->chave);
    memcpy(&tabela->vetor[onde], registro, sizeof(item));
}

void extract(hash* tabela, item* registro, int chave) {
    int onde = hashing(tabela, chave);
    if (tabela->vetor[onde].chave == chave) { // registro estah la?
        memcpy(registro, &tabela->vetor[onde], sizeof(item));
        memset(&tabela->vetor[onde], 0, sizeof(item));
    }
}

void print(const hash* tabela) {
    int i;
    for (i = 0; i < tabela->tamanho; ++i) {
        if (tabela->vetor[i].chave == 0) {
            printf("(vazio) ");
        } else {
            printf("<%d,%c> ", tabela->vetor[i].chave, tabela->vetor[i].valor);
        }
    }
}
