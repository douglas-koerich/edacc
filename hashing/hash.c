#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

// Definicao do estado de uma entrada da tabela de hashing
enum Estado {
    LIVRE,  // 0
    OCUPADA // 1
};
typedef enum Estado Estado;

// Definicao de uma entrada da tabela de hashing
struct Entrada {
    R dado;         // o registro armazenado
    Estado estado;  // se existe ou nao um registro nesta entrada da tabela
};
typedef struct Entrada Entrada;

struct Hash {
    size_t M;       // tamanho do vetor
    Entrada* vetor; // vetor de entradas (estado + dado)
};

// Implementacao da funcao de hashing (a que vai definir o indice no vetor
// a partir do valor da chave)
// (OBS.: escolheu-se o metodo pseudo-aleatorio)

static int h(unsigned chave, size_t tamanho) { // 1o. parametro eh a chave do registro
    srand(chave);
    int aleatorio = rand();
    int indice = aleatorio % tamanho;
    return indice;
}

// Implementacao das operacoes da interface

Hash* cria(size_t tamanho) {
    Hash* tabela = malloc(sizeof(Hash));
    tabela->M = tamanho;

    // Usa calloc porque ela inicializa a memoria com zeros, o que vai acabar
    // "armazenando" LIVRE (0) em todas as entradas :-) ...

    tabela->vetor = calloc(tamanho, sizeof(Entrada));

    return tabela;
}

void destroi(Hash* tabela) {
    free(tabela->vetor);
    free(tabela);
}

bool inserir(Hash* tabela, const R* registro) {
    int onde = h(registro->chave, tabela->M); // usa a funcao de hashing para
                                              // definir o local no vetor
    if (tabela->vetor[onde].estado == OCUPADA) {
        fprintf(stderr, "Posicao %d ocupada, insercao da chave %u abortada.\n",
                onde, registro->chave);
        return false;
    }
    memcpy(&tabela->vetor[onde].dado, registro, sizeof(R));
    tabela->vetor[onde].estado = OCUPADA;
    return true;
}

int busca(const Hash* tabela, unsigned chave) {
    int onde = h(chave, tabela->M); // usa a funcao de hashing pra recuperar o
                                    // local dessa chave na tabela
    if (tabela->vetor[onde].estado == LIVRE) {
        return -1; // chave nao encontrada
    }
    if (tabela->vetor[onde].dado.chave != chave) {
        return -1; // outro registro na posicao
    }
    return onde;
}

bool remover(Hash* tabela, R* destino, unsigned chave) {
    int onde = h(chave, tabela->M);
    if (tabela->vetor[onde].estado == LIVRE) {
        return false; // nao removeu nada (nao havia nada pra remover)
    }
    if (tabela->vetor[onde].dado.chave != chave) {
        return false; // o registro armazenado nao pode ser removido porque
                      // a sua chave de busca eh outra
    }
    memcpy(destino, &tabela->vetor[onde].dado, sizeof(R));
    tabela->vetor[onde].estado = LIVRE;
}

void debug(const Hash* tabela) {
    system("clear"); // limpa a tela
    int i;
    for (i=0; i<tabela->M; ++i) {
        // Transforma a chave (numero binario no registro) em uma string
        char str_chave[16];
        snprintf(str_chave, sizeof(str_chave), "%u", tabela->vetor[i].dado.chave);

        printf("[%d] {%c} %s\n", i, (tabela->vetor[i].estado == LIVRE? 'L': 'O'),
               (tabela->vetor[i].estado == LIVRE? "----": str_chave));
    }
}

