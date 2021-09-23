#include <stdio.h>
#include "lista.h"

struct node {
    int dado;
    struct node* proximo;
    struct node* anterior;
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
        l_extract(l, HEAD, 0);
    }
    free(l);
}

void l_insert(list* l, int v, where w, unsigned n) {
    if (l == NULL) {
        return;
    }
    node* p = malloc(sizeof(node));
    p->dado = v;
    if (l_underflow(l)) {
        w = HEAD;
    }
    if (w == POSN) {
        if (n <= 1) {
            w = HEAD;
        } else if (n > l_size(l)) {
            w = TAIL;
        }
    }
    switch (w) {
        case HEAD:
            p->anterior = NULL; // novo noh-cabeca nao terah um anterior
            p->proximo = l->cabeca;
            if (l->cabeca != NULL) { // jah existia uma cabeca na lista?
                // Esse noh (que agora serah o segundo) deve apontar para
                // o novo (que serah o primeiro) como anterior
                node* q = l->cabeca;
                q->anterior = p;
            }
            l->cabeca = p;
            if (p->proximo == NULL) { // eh o unico elemento da lista agora?
                l->cauda = p;
            }
            break;

        case TAIL: {
            p->proximo = NULL;
            node* q = l->cauda;
            p->anterior = q;
            q->proximo = l->cauda = p;
            break;
        }

        case POSN: {
            node* q = l->cabeca;
            int i = 1;
            while (i < n) {
                q = q->proximo;
                ++i;
            }
            p->proximo = q;
            node* a = q->anterior;
            p->anterior = a;

            a->proximo = p;
            q->anterior = p;
            break;
        }

        default:
            puts("Posicao invalida para insercao!");
            exit(EXIT_FAILURE);
    }
    ++l->tamanho;
}

int l_extract(list* l, where w, unsigned n) {
    if (l_underflow(l)) {
        return INT_MIN;
    }
    if (w == POSN) {
        if (n <= 1) {
            w = HEAD;
        } else if (n == l_size(l)) {
            w = TAIL;
        } else if (n > l_size(l)) {
            puts("Posicao indicada maior que o comprimento da lista");
            return INT_MIN;
        }
    }
    node* p = l->cabeca;
    switch (w) {
        case HEAD:
            l->cabeca = p->proximo;
            if (p->proximo == NULL) { // removendo o ultimo noh?
                l->cauda = NULL;
            } else { // um novo noh tomara o lugar como cabeca da lista
                node* q = p->proximo;
                q->anterior = NULL;
            }
            break;

        case TAIL: {
            p = l->cauda; // vai remover a cauda
            node* a = p->anterior;
            if (a != NULL) {
                a->proximo = NULL;
            } else {
                l->cabeca = NULL;
            }
            l->cauda = a;
            break;
        }

        case POSN: {
            int i = 1;
            while (i < n) {
                p = p->proximo;
                ++i;
            }
            node* a = p->anterior;
            node* q = p->proximo;
            a->proximo = q;
            q->anterior = a;
            break;
        }

        default:
            puts("Posicao invalida para remocao!");
            exit(EXIT_FAILURE);
    }
    int v = p->dado;
    free(p);
    --l->tamanho;
    return v;
}

bool l_search(const list* l, int v) {
    if (l == NULL) {
        return false;
    }
    node* p = l->cabeca;
    while (p != NULL) {
        if (p->dado == v) {
            return true;
        }
        p = p->proximo;
    }
    return false;
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
        printf("%d ", p->dado);
        p = p->proximo;
    }
    printf("(CAUDA)");
}

bool l_equal(const list* l1, const list* l2) {
    if (l1 == NULL || l2 == NULL) {
        return false;
    }
    node* p1 = l1->cabeca;
    node* p2 = l2->cabeca;

    while (p1 != NULL && p2 != NULL) {
        if (p1->dado != p2->dado) {
            return false;
        }
        p1 = p1->proximo;
        p2 = p2->proximo;
    }
    return p1 == p2; // retorna verdadeiro se ambos forem nulos (o laco
                     // terminou de percorrer AMBAS as listas)
}