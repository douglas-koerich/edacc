#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dicionario.h"
#include "lista.h"

#define TAMANHO_HASH 11 // normalmente um numero primo

struct Hash {
    Lista* vetor[TAMANHO_HASH];  
};

Hash* h_create(void) {
    Hash* h = malloc(sizeof(Hash));
    size_t i;
    for (i = 0; i < TAMANHO_HASH; ++i) {
        h->vetor[i] = create();
    }
    return h;
}

void h_destroy(Hash* h) {
    size_t i;
    for (i = 0; i < TAMANHO_HASH; ++i) {
        destroy(h->vetor[i]);
    }
    free(h);
}

static int hashing(int chave) { // parametro eh int porque a chave do registro
                                // eh int (deve ser do tipo correspondente)
    // Metodos validos para uma funcao de hashing
    int indice;

    /* 1. Metodo da divisao
    indice = chave % TAMANHO_HASH;

    // 2. Metodo pseudo-aleatorio
    srand(chave); // usa chave como semente de valores aleatorios
    indice = rand() % TAMANHO_HASH; // limita o numero randomico ao tamanho da 
                                    //tabela
    */

    // 3. Metodo do meio-quadrado
    int quadrado = chave * chave; // obtem um valor com ate 6 digitos
    int meio = (quadrado / 100) % 100; // extrai os 2 digitos intermediarios
    indice = meio % TAMANHO_HASH; // normaliza para o intervalo 0-(n-1)

    return indice;
}

Registro* h_search(const Hash* h, int x) {
    int posicao = hashing(x); // calcula a posicao onde deve buscar a chave x
    return search(h->vetor[posicao], x);
}

void h_insert(Hash* h, const Registro* r) {
    int posicao = hashing(r->chave); // calcula a posicao correspondente da
                                     // nova chave (mapeamento)
    Registro* reg = search(h->vetor[posicao], r->chave);
    if (reg != NULL) {
        printf("Chave %d ja existe no dicionario, atualizando valor...\n",
               r->chave);
        reg->valor = r->valor;
    } else {
        insert(h->vetor[posicao], r, CABECA, 0);
    }
}

void h_extract(Hash* h, Registro* r, int x) {
    int posicao = hashing(x); // calcula a posicao onde deve buscar a chave x
    r->chave = x; // porque a funcao extract() da lista busca a chave dentro
                  // do parametro r
    extract(h->vetor[posicao], r, VALOR, 0);
}

void h_print(const Hash* h) {
    size_t i;
    for (i = 0; i < TAMANHO_HASH; ++i) {
        printf("%2zd: ", i);
        if (underflow(h->vetor[i])) {
            puts("(vazio)");
        } else {
            print(h->vetor[i]);
            putchar('\n');
        }
    }
} 
