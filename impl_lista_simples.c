#include <stdlib.h>
#include <stdio.h>
#include "tad_lista_linear.h"

struct Noh {
    Registro elemento;
    struct Noh* proximo;    // link para o seguinte na lista
};
typedef struct Noh Noh;

struct ListaReg {
    Noh* cabeca;    // endereco do primeiro noh
};

ListaReg* criar(void) {
    ListaReg* l = (ListaReg*) malloc(sizeof(ListaReg));
    l->cabeca = NULL;   // lista vazia
    return l;
}

void destruir(ListaReg* l) {
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

bool underflow(const ListaReg* l) {
    return l == NULL || l->cabeca == NULL;
}

void imprimir(const ListaReg* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("(Cabeca) ");
    Noh* i = l->cabeca;
    while (i != NULL) {
        printf("[%d,%s]-->", i->elemento.chave, i->elemento.nome);
        i = i->proximo;
    }
    printf("|| (Cauda)");
}

Registro* buscar(const ListaReg* l, int x) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* i = l->cabeca;
    while (i != NULL) { // enquanto nao chega ao fim da lista...
        if (i->elemento.chave == x) {
            return &i->elemento;
        }
        i = i->proximo;
    }
    return NULL;    // nao encontrado
}

void inserir_cabeca(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    n->proximo = l->cabeca;
    l->cabeca = n;
}

void inserir_cauda(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    n->proximo = NULL;
    if (l->cabeca == NULL) {    // lista ainda vazia?
        l->cabeca = n;
        return;
    }
    Noh* i = l->cabeca;
    while (i->proximo != NULL) {    // enquanto nao estiver no ultimo
        i = i->proximo;
    }
    // Laco termina com `i` sobre o ultimo noh
    i->proximo = n;
}

void inserir_ordem(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    Noh* i = l->cabeca;
    Noh* anterior_i = NULL;   // para lembrar quem eh o anterior do noh
    while (i != NULL && i->elemento.chave < n->elemento.chave) {
        anterior_i = i;
        i = i->proximo;
    }
    n->proximo = i;
    if (anterior_i == NULL) {
        // Lista estava vazia:
        l->cabeca = n;
    } else {
        anterior_i->proximo = n;
    }
}

Registro remover_cabeca(ListaReg* l) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    Registro r = x->elemento;
    free(x);
    return r;
}

Registro remover_cauda(ListaReg* l) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cabeca;
    Noh* anterior_x = NULL;
    while (x->proximo != NULL) {
        anterior_x = x; // "lembra" quem eh o anterior...
        x = x->proximo; // ... e entao vai para o proximo
    }
    Registro r = x->elemento;
    free(x);
    // Se o ultimo noh (x) for tambem o primeiro (e unico),
    // nao existe um anterior; do contrario, o que deve ser
    // sinalizado como NULL eh o ponteiro para a cabeca
    if (anterior_x == NULL) {
        l->cabeca = NULL;   // lista ficou vazia (de novo)
    } else {
        anterior_x->proximo = NULL;
    }
    return r;
}

Registro remover_chave(ListaReg* l, int x) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* i = l->cabeca;
    Noh* anterior_i = NULL;
    while (i != NULL && i->elemento.chave != x) {
        anterior_i = i;
        i = i->proximo;
    }
    if (i == NULL) {
        Registro vazio = { 0 };
        return vazio;
    }
    if (anterior_i == NULL) {
        l->cabeca = i->proximo;
    } else {
        anterior_i->proximo = i->proximo;
    }
    Registro r = i->elemento;
    free(i);
    return r;
}
