#include <stdlib.h>
#include <stdio.h>
#include "exerc4lista05.h"

struct Noh {
    int elemento;
    struct Noh* proximo;
    struct Noh* anterior;
};
typedef struct Noh Noh;

struct ListaInt {
    Noh* cabeca;
};

ListaInt* criar(void) {
    ListaInt* l = (ListaInt*) malloc(sizeof(ListaInt));
    l->cabeca = NULL;
    return l;
}

void destruir(ListaInt* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        remover_cabeca(l);
    }
    free(l);
}

bool underflow(const ListaInt* l) {
    return l == NULL || l->cabeca == NULL;
}

void imprimir(const ListaInt* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("(Cabeca) ||<");
    Noh* i = l->cabeca;
    while (i != NULL) {
        printf("-->[%d]<", i->elemento);
        i = i->proximo;
    }
    printf("-->|| (Cauda)");
}

void inserir_cabeca(ListaInt* l, int n) {
    if (l == NULL) {
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    noh->proximo = l->cabeca;
    noh->anterior = NULL; 
    if (l->cabeca != NULL) {
        l->cabeca->anterior = noh;
    }
    l->cabeca = noh;
}

int remover_cabeca(ListaInt* l) {
    if (underflow(l)) {
        return 0;
    }
    Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    if (l->cabeca != NULL) {
        l->cabeca->anterior = NULL;
    }
    int n = x->elemento;
    free(x);
    return n;
}

static void troca(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

// Exercicio 4
void coqueteleira(ListaInt* l) {
    if (underflow(l)) {
        return;
    }
    // Alem de fazer a primeira passagem "descendo" o maior elemento em direcao
    // do fim da lista, conta quantos nohs ela tem pra controlar
    // o numero de passagens necessarias
    size_t i = 1, t = 1;
    while (i <= t) {
        Noh* j = l->cabeca;
        // Inicia a varredura do inicio para o fim, levando os maiores para frente
        while (j->proximo != NULL) {
            if (j->elemento > j->proximo->elemento) {
                troca(&j->elemento, &j->proximo->elemento);
            }
            j = j->proximo;
            if (i == 1) { // primeira passagem
                ++t;      // conta o numero de nohs para balizar o numero de varreduras
            }
        }
        printf("\nLevando maior na %zda. varredura:\n", i);
        imprimir(l);
        // Continua a varredura no sentido inverso, levando os menores para tras
        while (j->anterior != NULL) {
            if (j->elemento < j->anterior->elemento) {
                troca(&j->elemento, &j->anterior->elemento);
            }
            j = j->anterior;
        }
        printf("\nLevando menor na %zda. varredura:\n", i);
        imprimir(l);
        ++i;    // varredura completa
    }
}
