#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

struct Hash {
    Reg* vetor; // alocado dinamicamente na criacao
    size_t m; // comprimento do vetor originalmente alocado
    size_t n; // numero de registros armazenados na tabela
    unsigned M; // fator de ajuste para o tamanho na funcao de hashing
};

// Funcao auxiliar que calcula o maior numero primo maior que dado numero
static unsigned primo_maior(unsigned num) {
    bool eh_primo = false;
    unsigned teste = num;
    while (!eh_primo) {
        eh_primo = true;
        int inter;
        for (inter = 2; inter < teste; ++inter) {
            if (teste % inter == 0) {
                eh_primo = false;
                break;
            }
        }
        if (eh_primo == false) {
            ++teste;
        }
    }
    return teste;
}

Hash* criar(size_t num_total_posicoes) {
    Hash* h = malloc(sizeof(Hash));
    h->n = 0; // nenhum elemento armazenado
    h->m = num_total_posicoes; // capacidade do vetor
    h->M = primo_maior(h->m);
    h->vetor = calloc(h->m, sizeof(Reg)); // aloca vetor de registros
    return h;
}

void destruir(Hash* h) {
    free(h->vetor);
    free(h);
}

// Funcao de hashing utilizada para calcular a posicao com base
// no valor da chave
static int hashing(const Hash* h, unsigned chave) {
#if 0
    // Metodo da divisao
    int posicao = chave % h->M;
#else
    // Metodo pseudo-aleatorio
    srand(chave); // chave eh a semente da sequencia pseudo-aleatoria
    int posicao = rand() % h->M;
#endif
    if (posicao >= h->m) { // se o resto eh maior que o ultimo indice...
        posicao -= h->m;
    }
#ifdef DEBUG
    printf("Para a chave %u foi definida a posicao %d\n", chave, posicao);
#endif
    return posicao;
}

void inserir(Hash* h, const Reg* r) {
    // Calcula a posicao onde serah armazenado o novo registro
    int posicao = hashing(h, r->chave);

    if (h->vetor[posicao].chave != 0) {
        printf("*** COLISAO da chave %u com a sinonima %u! ***\n", r->chave,
               h->vetor[posicao].chave);
    }
    // Armazena o registro no indice correspondente do vetor
    memcpy(h->vetor + posicao, r, sizeof(Reg));
}

Reg* buscar(const Hash* h, unsigned chave) {
    // Chama a mesma funcao que calculou a posicao de insercao
    // dessa chave (se existe) na tabela
    int posicao = hashing(h, chave);

    // Nao eh necessario percorrer o vetor, vamos diretamente ao indice
    // indicado pela funcao; porem, o registro pode nao estar (ainda) ali
    if (h->vetor[posicao].chave == chave) {
        return h->vetor + posicao; // retorna o endereco do registro existente
    }
    return NULL; // posicao nao contem a chave informada
}

size_t tamanho(const Hash* h) {
    return h->n; // numero de elementos armazenados na tabela
}

void imprimir(const Hash* h) {
#ifdef DEBUG
    int i;
    for (i = 0; i < h->m; ++i) {
        if (h->vetor[i].chave == 0) {
            printf("(<vazio>) ");
        } else {
            printf("(%u,%c) ", h->vetor[i].chave, h->vetor[i].dado);
        }
    }
    putchar('\n');
#endif
}

