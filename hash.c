#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

// Cada item/elemento da tabela hash
struct item {
    bool livre;     // item/elemento/celula da tabela nao ocupada
    Registro info;
    int proximo;    // encadeamento interior
};
typedef struct item Item;

// Implementacao do TAD com tratamento por encadeamento interior
struct hash {
    Item* tabela;           // posicoes indicadas pela funcao de hash
    Item* extensao;         // para chaves colidentes (encad. interior)
    size_t tamanho_tabela;  // tamanho (primo) da tabela hash
    size_t tamanho_extensao;
    size_t contador;        // considera apenas o uso da extensao
};

// Dimensiona a tabela hash segundo um numero primo para usarmos
// a normalizacao ("metodo da divisao") com distribuicao mais uniforme
static size_t maior_primo(size_t x) {
    size_t p = x;
    bool primo;
    do {
        primo = true;
        size_t d = p - 1;
        while (d > 1 && primo == true) {
            if (p % d == 0) {
                primo = false;
            }
            --d;
        }
        if (primo == false) {
            ++p;
        }
    } while (primo == false);
    return p;
}

Hash* criar(size_t tamanho) {
    if (tamanho <= 0) {
        return NULL;
    }
    Hash* h = malloc(sizeof(Hash));
    h->tamanho_tabela = maior_primo(tamanho);
    h->tamanho_extensao = tamanho;
    h->contador = 0;
    h->tabela = malloc(sizeof(Item) * h->tamanho_tabela);
    h->extensao = malloc(sizeof(Item) * tamanho);
    int i;
    for (i = 0; i < h->tamanho_tabela; ++i) {
        h->tabela[i].livre = true;
        h->tabela[i].proximo = -1; // "lista encadeada" vazia
    }
    for (i = 0; i < h->tamanho_extensao; ++i) {
        h->extensao[i].livre = true;
        h->extensao[i].proximo = -1; // "lista encadeada" vazia
    }
    return h;
}

void destruir(Hash* tabela) {
    if (tabela == NULL) {
        return;
    }
    free(tabela->tabela);
    free(tabela->extensao);
    free(tabela);
}

bool overflow(const Hash* tabela) {
    if (tabela == NULL) {
        return false;
    }
    return tabela->tamanho_extensao == tabela->contador;
}

// Funcao de hash
static int funcao_hash(const Hash* tabela, int chave) {
    int posicao;
    srand(chave);
    posicao = rand() % tabela->tamanho_tabela;
    return posicao;
}

Registro* buscar(const Hash* tabela, int chave) {
    int posicao = funcao_hash(tabela, chave);
    Item* i = &tabela->tabela[posicao];
    if (i->livre == true) {
        return NULL;
    }
    while (i->proximo != -1 && i->info.chave != chave) {
        i = &tabela->extensao[i->proximo];
    }
    if (i->info.chave == chave) {
        return &i->info;
    }
    return NULL;
}

bool inserir(Hash* tabela, const Registro* novo) {
    int posicao = funcao_hash(tabela, novo->chave);

    // Tenta armazenar na tabela hash
    Item* i = &tabela->tabela[posicao];
    if (i->livre == true) {
        memcpy(&i->info, novo, sizeof(Registro));
        i->livre = false;
        return true;
    }
    if (overflow(tabela)) {
        return false;
    }
    // Vai para a extensao
    while (i->proximo != -1 && i->info.chave != novo->chave) {
        i = &tabela->extensao[i->proximo];
    }
    if (i->info.chave == novo->chave) {
        memcpy(&i->info, novo, sizeof(Registro));   // sobrescreve
        return true;
    }
    // Terminei de percorrer as sinonimas sem encontrar a propria
    memcpy(&tabela->extensao[tabela->contador].info, novo, sizeof(Registro));
    tabela->extensao[tabela->contador].livre = false;
    i->proximo = tabela->contador++;
    return true;
}

void remover(Hash* tabela, int chave) {}

void imprimir(const Hash* tabela) {
    puts("\nTABELA HASH");
    int i;
    for (i = 0; i < tabela->tamanho_tabela; ++i) {
        if (tabela->tabela[i].livre == true) {
            printf("[%02d] (Livre)\n", i);
        } else {
            printf("[%02d] (%d,%c) --> %d\n", i, tabela->tabela[i].info.chave,
            tabela->tabela[i].info.dado, tabela->tabela[i].proximo);
        }
    }
    puts("\nEXTENSAO");
    for (i = 0; i < tabela->contador; ++i) {
        printf("[%02d] (%d,%c) --> %d\n", i, tabela->extensao[i].info.chave,
        tabela->extensao[i].info.dado, tabela->extensao[i].proximo);
    }
    printf("... (%zd posicoes livres) ...\n",
           tabela->tamanho_extensao - tabela->contador);
}

