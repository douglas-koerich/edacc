#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "registro.h"
#include "lista.h"
#include "hash.h"

struct hash {
    lista** tabela;
    size_t tamanho;
};

static int funcao_hash(unsigned short chave, size_t tamanho) {
    srand(chave);
    return rand() % tamanho;
}

hash* cria_h(size_t t) {
    hash* h = (hash*) malloc(sizeof(hash));
    h->tabela = (lista**) malloc(t * sizeof(lista*));
    int i;
    for (i=0; i<t; ++i) {
        h->tabela[i] = cria();
    }
    h->tamanho = t;
    return h;
}

void destroi_h(hash* h) {
    if (h == NULL) {
        return;
    }
    int i;
    for (i=0; i<h->tamanho; ++i) {
        destroi(h->tabela[i]);
    }
    free(h->tabela);
    free(h);
}

void inserir_h(hash* h, const registro* r) {
    if (h == NULL) {
        return;
    }
    int posicao = funcao_hash(r->chave, h->tamanho);
    insere_atualiza(h->tabela[posicao], r);
}

registro* busca_h(const hash* h, unsigned short x) {
    if (h == NULL) {
        return NULL;
    }
    int posicao = funcao_hash(x, h->tamanho);
    return busca(h->tabela[posicao], x);
}

void imprime_h(const hash* h) {
    if (h == NULL) {
        return;
    }
    int i;
    for (i=0; i<h->tamanho; ++i) {
        printf("{%2d} ", i);
        imprime(h->tabela[i]);
        putchar('\n');
    }
}
