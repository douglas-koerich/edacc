#include <stdlib.h>
#include <stdio.h>
#include "exerc1lista02.h"

struct Noh {
    int elemento;
    struct Noh* proximo;    // link para o seguinte na lista
};
typedef struct Noh Noh;

struct ListaInt {
    Noh* cabeca;    // endereco do primeiro noh
};

ListaInt* criar(void) {
    ListaInt* l = (ListaInt*) malloc(sizeof(ListaInt));
    l->cabeca = NULL;   // lista vazia
    return l;
}

void destruir(ListaInt* l) {
    if (l == NULL) {
        return;
    }
    // Eh necessario esvaziar a lista antes de remover a referencia
    // ao noh-cabeca
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
    printf("(Cabeca) ");
    Noh* i = l->cabeca;
    while (i != NULL) {
        printf("[%d]-->", i->elemento);
        i = i->proximo;
    }
    printf("|| (Cauda)");
}

bool existe(const ListaInt* l, int n) {
    if (underflow(l)) {
        return false;
    }
    Noh* i = l->cabeca;
    while (i != NULL) { // enquanto nao chega ao fim da lista...
        if (i->elemento == n) {
            return true;
        }
        i = i->proximo;
    }
    return false;    // nao encontrado
}

void inserir_cabeca(ListaInt* l, int n) {
    if (l == NULL || existe(l, n)) { // impede a insercao de duplicata...
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    noh->proximo = l->cabeca;
    l->cabeca = noh;
}

void inserir_cauda(ListaInt* l, int n) {
    if (l == NULL || existe(l, n)) {
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    noh->proximo = NULL;
    if (l->cabeca == NULL) {    // lista ainda vazia?
        l->cabeca = noh;
        return;
    }
    Noh* i = l->cabeca;
    while (i->proximo != NULL) {    // enquanto nao estiver no ultimo
        i = i->proximo;
    }
    // Laco termina com `i` sobre o ultimo noh
    i->proximo = noh;
}

void inserir_ordem(ListaInt* l, int n) {
    if (l == NULL || existe(l, n)) {
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    Noh* i = l->cabeca;
    Noh* anterior_i = NULL;   // para lembrar quem eh o anterior do noh
    while (i != NULL && i->elemento < n) {
        anterior_i = i;
        i = i->proximo;
    }
    noh->proximo = i;
    if (anterior_i == NULL) {
        // Lista estava vazia:
        l->cabeca = noh;
    } else {
        anterior_i->proximo = noh;
    }
}

int remover_cabeca(ListaInt* l) {
    if (underflow(l)) {
        return -1;
    }
    Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    int n = x->elemento;
    free(x);
    return n;
}

int remover_cauda(ListaInt* l) {
    if (underflow(l)) {
        return -1;
    }
    Noh* x = l->cabeca;
    Noh* anterior_x = NULL;
    while (x->proximo != NULL) {
        anterior_x = x; // "lembra" quem eh o anterior...
        x = x->proximo; // ... e entao vai para o proximo
    }
    int n = x->elemento;
    free(x);
    // Se o ultimo noh (x) for tambem o primeiro (e unico),
    // nao existe um anterior; do contrario, o que deve ser
    // sinalizado como NULL eh o ponteiro para a cabeca
    if (anterior_x == NULL) {
        l->cabeca = NULL;   // lista ficou vazia (de novo)
    } else {
        anterior_x->proximo = NULL;
    }
    return n;
}

void remover_valor(ListaInt* l, int n) {
    if (underflow(l)) {
        return;
    }
    Noh* i = l->cabeca;
    Noh* anterior_i = NULL;
    while (i != NULL && i->elemento != n) {
        anterior_i = i;
        i = i->proximo;
    }
    if (i == NULL) {
        return;
    }
    if (anterior_i == NULL) {
        l->cabeca = i->proximo;
    } else {
        anterior_i->proximo = i->proximo;
    }
    free(i);
}

/* A operacao de concatenacao vai invalidar o ponteiro
   da segunda lista (que foi anexada na primeira), pois
   a ListaInt que ele aponta vai ser liberada da memoria */

void concatenar(ListaInt* l1, ListaInt* l2) {
    if (l1 == NULL || l2 == NULL) {
        return;
    }
    if (underflow(l2)) {
        return; // nao ha o que concatenar...
    }
    if (underflow(l1)) {
        l1->cabeca = l2->cabeca; // move a sequencia de nohs para l1
        l2->cabeca = NULL;       // invalida o ponteiro para a segunda lista
        free(l2);                // remove esse ponteiro gerado na funcao criar()
        return;
    }
    // Inicia o processo de concatenacao removendo as
    // duplicatas da segunda lista
    Noh* i = l1->cabeca;
    while (i != NULL) { // para todos os nohs da primeira lista...
        if (existe(l2, i->elemento)) { // ... verifica se existe na segunda...
            remover_valor(l2, i->elemento); // ... e se existir remove duplicata
        }
        i = i->proximo;
    }
    // Concatena a segunda lista na primeira
    i = l1->cabeca;
    while (i->proximo != NULL) { // para no ultimo noh
        i = i->proximo;
    }
    i->proximo = l2->cabeca;
    l2->cabeca = NULL;
    free(l2);
}
