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
    Noh* cauda;     // endereco do ultimo noh
    size_t tamanho; // numero de nohs da lista encadeada
};

ListaReg* criar(void) {
    ListaReg* l = (ListaReg*) malloc(sizeof(ListaReg));
    l->cabeca = NULL;   // lista vazia
    l->cauda = NULL;
    l->tamanho = 0;
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
    return l == NULL || l->tamanho == 0;
}

void imprimir(const ListaReg* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("{%zd nohs} (Cabeca) ", l->tamanho);
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
    if (l->cauda == NULL) { // lista estava vazia?
        l->cauda = n;   // n eh o primeiro mas tambem o ultimo
    }
    ++l->tamanho;
}

void inserir_cauda(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    n->proximo = NULL;
    if (l->cauda != NULL) {     // existe um ultimo noh?
        l->cauda->proximo = n;
    } else {    // se nao existe ultimo, a lista estah vazia
        l->cabeca = n;
    }
    l->cauda = n;
    ++l->tamanho;
}

void inserir_ordem(ListaReg* l, const Registro* r) {
    // TODO:
    return;
}

Registro remover_cabeca(ListaReg* l) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    if (l->cabeca == NULL) {    // nao existe mais um primeiro?
        l->cauda = NULL;    // entao nao existe tambem um ultimo...
    }
    --l->tamanho;
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
    while (x != l->cauda) {
        anterior_x = x; // "lembra" quem eh o anterior...
        x = x->proximo; // ... e entao vai para o proximo
    }
    Registro r = x->elemento;
    free(x);
    // Se o ultimo noh (x) for tambem o primeiro (e unico),
    // nao existe um anterior; do contrario, o que deve ser
    // sinalizado como NULL eh o ponteiro para a cabeca
    if (anterior_x == NULL) {
        l->cabeca = l->cauda = NULL;   // lista ficou vazia (de novo)
    } else {
        anterior_x->proximo = NULL;
        l->cauda = anterior_x;
    }
    --l->tamanho;
    return r;
}

Registro remover_chave(ListaReg* l, int x) {
    // TODO:
    Registro r;
    return r;
}
