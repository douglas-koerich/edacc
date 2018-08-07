#include <stdlib.h>
#include <stdio.h>
#include "tad_lista_linear.h"

struct Noh {
    Registro elemento;
    struct Noh* proximo;    // link para o seguinte na lista
};
typedef struct Noh Noh;

struct ListaReg {
    Noh* cauda;    // na lista circular, o endereco visivel externamente eh o da cauda
};

ListaReg* criar(void) {
    ListaReg* l = (ListaReg*) malloc(sizeof(ListaReg));
    l->cauda = NULL;   // lista vazia
    return l;
}

void destruir(ListaReg* l) {
    if (l == NULL) {
        return;
    }
    // Eh necessario esvaziar a lista antes de remover a referencia
    // ao noh-cauda
    while (!underflow(l)) {
        remover_cabeca(l);
    }
    free(l);
}

bool underflow(const ListaReg* l) {
    return l == NULL || l->cauda == NULL;
}

void imprimir(const ListaReg* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("(Cabeca) ");
    Noh* i = l->cauda;
    do {
        i = i->proximo;
        printf("[%d,%s]-->", i->elemento.chave, i->elemento.nome);
    } while (i != l->cauda);
    printf("|| (Cauda)");
}

Registro* buscar(const ListaReg* l, int x) {
    if (underflow(l)) {
        return NULL;
    }
    Noh* i = l->cauda;
    do {
        i = i->proximo;
        if (i->elemento.chave == x) {
            return &i->elemento;
        }
    } while (i != l->cauda);
    return NULL;    // nao encontrado
}

void inserir_cauda(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    if (l->cauda == NULL) {
        n->proximo = n;
    } else {
        n->proximo = l->cauda->proximo;
        l->cauda->proximo = n;
    }
    l->cauda = n;
}

void inserir_cabeca(ListaReg* l, const Registro* r) {
    if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->elemento = *r;
    if (l->cauda == NULL) {
        n->proximo = n;
        l->cauda = n;
    } else {
        n->proximo = l->cauda->proximo;
        l->cauda->proximo = n;
    }
}

void inserir_ordem(ListaReg* l, const Registro* r) {
    return;
}

Registro remover_cabeca(ListaReg* l) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cauda;
    x = x->proximo; // vai para a cabeca
    Registro r = x->elemento;
    if (x == x->proximo) {  // cabeca = cauda?
        l->cauda = NULL;
    } else {
        l->cauda->proximo = x->proximo;
    }
    free(x);
    return r;
}

Registro remover_cauda(ListaReg* l) {
    if (underflow(l)) {
        Registro vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cauda;
    Registro r = x->elemento;
    if (x == x->proximo) {
        l->cauda = NULL;
    } else {
        Noh* anterior_x = x->proximo;   // comeca a busca pelo penultimo na cabeca
        while (anterior_x->proximo != x) {
            anterior_x = anterior_x->proximo;
        }
        anterior_x->proximo = x->proximo;
        l->cauda = anterior_x;
    }
    free(x);
    return r;
}

Registro remover_chave(ListaReg* l, int x) {
    Registro vazio = { 0 };
    return vazio;
}
