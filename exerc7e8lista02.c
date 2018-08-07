#include <stdlib.h>
#include <stdio.h>
#include "exerc7e8lista02.h"
#include "novo_tad_pilha_inteiros.h"

struct Noh {
    int elemento;
    struct Noh* proximo;    // link para o seguinte na lista
};
typedef struct Noh Noh;

struct ListaInt {
    Noh* cauda;    // na lista circular, o endereco visivel externamente eh o da cauda
};

ListaInt* criar(void) {
    ListaInt* l = (ListaInt*) malloc(sizeof(ListaInt));
    l->cauda = NULL;   // lista vazia
    return l;
}

void destruir(ListaInt* l) {
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

bool underflow(const ListaInt* l) {
    return l == NULL || l->cauda == NULL;
}

void imprimir(const ListaInt* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("(Cabeca) ");
    Noh* i = l->cauda;
    do {
        i = i->proximo;
        printf("[%d]-->", i->elemento);
    } while (i != l->cauda);
    printf("|| (Cauda)");
}

void inserir_cabeca(ListaInt* l, int n) {
    if (l == NULL) {
        return;
    }
    Noh* noh = (Noh*) malloc(sizeof(Noh));
    noh->elemento = n;
    if (l->cauda == NULL) {
        noh->proximo = noh;
        l->cauda = noh;
    } else {
        noh->proximo = l->cauda->proximo;
        l->cauda->proximo = noh;
    }
}

int remover_cabeca(ListaInt* l) {
    if (underflow(l)) {
        return 0;
    }
    Noh* x = l->cauda;
    x = x->proximo; // vai para a cabeca
    int n = x->elemento;
    if (x == x->proximo) {  // cabeca = cauda?
        l->cauda = NULL;
    } else {
        l->cauda->proximo = x->proximo;
    }
    free(x);
    return n;
}

// Exercicio 7
size_t tamanho(const ListaInt* l) {
    if (underflow(l)) {
        return 0;
    }
    size_t n = 0;
    Noh* i = l->cauda;
    do {
        i = i->proximo;
        ++n;
    } while (i != l->cauda);
    return n;
}

// Exercicio 8
void inverter(ListaInt* l) {
    if (underflow(l)) {
        return;
    }
    PilhaInt* p = cria();
    Noh* i = l->cauda;
    do {
        i = i->proximo;
        push(p, i->elemento);
    } while (i != l->cauda);
    do {
        i = i->proximo;
        i->elemento = pop(p);
    } while (i != l->cauda);
    destroi(p);
}
