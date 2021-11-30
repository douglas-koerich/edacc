#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "hash.h"
#include "lista_itens.h"

struct hash {
    list** vetor;   // vetor de ponteiros (list* vetor[] -> (list*)* vetor)
    size_t tamanho;
};

hash* create(size_t tamanho) {
    hash* nova = malloc(sizeof(hash));
    nova->vetor = malloc(tamanho * sizeof(list*));
    int i;
    for (i = 0; i < tamanho; ++i) {
        nova->vetor[i] = l_create();
    }
    nova->tamanho = tamanho;
    return nova;
}

void destroy(hash* tabela) {
    int i;
    for (i = 0; i < tabela->tamanho; ++i) {
        l_destroy(tabela->vetor[i]);
    }
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
    return l_search(tabela->vetor[onde], chave);
}

void insert(hash* tabela, const item* registro) {
    int onde = hashing(tabela, registro->chave);
    l_insert(tabela->vetor[onde], registro); // a funcao deveria ATUALIZAR o
                                             // noh se a chave jah existisse
                                             // na lista!
}

bool extract(hash* tabela, item* registro, int chave) {
    int onde = hashing(tabela, chave);
    return l_extract(tabela->vetor[onde], registro, chave); 
}

void print(const hash* tabela) {
    int i;
    for (i = 0; i < tabela->tamanho; ++i) {
        l_print(tabela->vetor[i]);
        putchar('\n');
    }
}
