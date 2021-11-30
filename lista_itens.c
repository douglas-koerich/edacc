#include <stdio.h>
#include <string.h>
#include "lista_itens.h"

struct node {
    item dado;
    struct node* link;
};
typedef struct node node;

struct list {
    node* cabeca;
    node* cauda;
    size_t tamanho;
};

list* l_create(void) {
    list* nova = malloc(sizeof(list));
    nova->cabeca = nova->cauda = NULL;
    nova->tamanho = 0;
    return nova;
}

void l_destroy(list* l) {
    if (l == NULL) {
        return;
    }
    while (!l_underflow(l)) {
        node* p = l->cabeca;
        l->cabeca = p->link;
        if (p->link == NULL) {
            l->cauda = NULL;
        }
        free(p);
    }
    free(l);
}

void l_insert(list* l, const item* i) {
    if (l == NULL) {
        return;
    }
    node* p = malloc(sizeof(node));
    memcpy(&p->dado, i, sizeof(item));
    if (l_underflow(l)) {
        p->link = l->cabeca;
        l->cabeca = p;
        if (p->link == NULL) {
            l->cauda = p;
        }
    } else {
        p->link = NULL;
        node* q = l->cauda;
        q->link = l->cauda = p;
    }
    ++l->tamanho;
}

bool l_extract(list* l, item* i, int k) {
    if (l_underflow(l)) {
        return false;
    }
    node* p = l->cabeca;
    node* a = NULL;
    while (p != NULL && p->dado.chave != k) {
        a = p;
        p = p->link;
    }
    if (p != NULL) {
        memcpy(i, &p->dado, sizeof(item));
        if (a != NULL) {
            a->link = p->link;
        } else {
            l->cabeca = p->link;
        }
        free(p);
        --l->tamanho;
        return true;
    } else {
        return false;
    }
}

item* l_search(const list* l, int k) {
    if (l == NULL) {
        return false;
    }
    node* p = l->cabeca;
    while (p != NULL) {
        if (p->dado.chave == k) {
            return &p->dado;
        }
        p = p->link;
    }
    return NULL;
}

size_t l_size(const list* l) {
    if (l == NULL) {
        return 0;
    }
    return l->tamanho;
}

bool l_underflow(const list* l) {
    return l == NULL || l->cabeca == NULL;
}

void l_print(const list* l) {
    if (l_underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    node* p = l->cabeca;
    while (p != NULL) {
        printf("<%d,%c> ", p->dado.chave, p->dado.valor);
        p = p->link;
    }
    printf("(CAUDA)");
}
