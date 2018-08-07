#include <stdlib.h>
#include <stdio.h>
#include "tad_lista_linear.h"

struct Noh {
    Registro elemento;
    struct Noh* proximo;    // link para o seguinte na lista
    struct Noh* anterior;   // link para o anterior na lista
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
    printf("\n(Cabeca) ||<");
    Noh* i = l->cabeca;
    while (i != NULL) {
        printf("-->[%d,%s]<", i->elemento.chave, i->elemento.nome);
        i = i->proximo;
    }
    printf("-->|| (Cauda)");
    // Para ilustrar a utilidade da lista duplamente encadeada, vou imprimir a
    // mesma no sentido inverso
    printf("\n(Cauda) ||<");
    i = l->cabeca;
    while (i->proximo != NULL) {    // procura o fim da lista
        i = i->proximo;
    }
    do {
        printf("-->[%d,%s]<", i->elemento.chave, i->elemento.nome);
        i = i->anterior;
    } while (i != NULL);
    printf("-->|| (Cabeca)");
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
    n->anterior = NULL; // eh o novo primeiro noh, que nao tem anterior
    if (l->cabeca != NULL) {        // ja existe um primeiro noh?
        l->cabeca->anterior = n;    // ele passa a ser o segundo, apontando para o novo primeiro
    }
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
        n->anterior = NULL; // novo ultimo noh eh tambem o novo primeiro
        return;
    }
    Noh* i = l->cabeca;
    while (i->proximo != NULL) {    // enquanto nao estiver no ultimo
        i = i->proximo;
    }
    // Laco termina com `i` sobre o ultimo noh
    i->proximo = n;
    n->anterior = i;    // o novo ultimo aponta para o antigo ultimo como anterior
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
    if (l->cabeca != NULL) {    // existia um segundo que se tornou o primeiro?
        l->cabeca->anterior = NULL;
    }
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
    while (x->proximo != NULL) {
        x = x->proximo;
    }
    Registro r = x->elemento;
    free(x);
    if (x->anterior == NULL) {  // era o ultimo mas tambem o primeiro?
        l->cabeca = NULL;   // lista ficou vazia (de novo)
    } else {
        x->anterior->proximo = NULL;
    }
    return r;
}

Registro remover_chave(ListaReg* l, int x) {
    // TODO:
    Registro r;
    return r;
}
