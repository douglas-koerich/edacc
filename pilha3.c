#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "pilha.h"
#include "lista.h"

struct pilha {
    list* l;
};

pilha* create(size_t max) {
    pilha* nova = malloc(sizeof(pilha));
    nova->l = l_create();
    return nova;
}

void destroy(pilha* p) {
    if (p == NULL) {
        return;
    }
    l_destroy(p->l);
    free(p);
}

void push(pilha* p, int v) {
    if (p == NULL) {
        return;
    }
    l_insert(p->l, v, HEAD, 0);
}

int pop(pilha* p) {
    if (p == NULL || l_underflow(p->l)) {
        return INT_MIN;
    }
    return l_extract(p->l, HEAD, 0);
}

int top(const pilha* p) {
    if (p == NULL) {
        return INT_MIN;
    }
    return l_head(p->l);
}

size_t size(const pilha* p) {
    if (p == NULL) {
        return 0;
    }
    return l_size(p->l);
}

bool underflow(const pilha* p) {
    if (p == NULL) {
        return true;
    }
    return l_underflow(p->l);
}

void print(const pilha* p) {
    if (p == NULL) {
        return;
    }
    if (l_underflow(p->l)) {
        puts("(VAZIA)");
        return;
    }
    printf("(TOPO) ");
    l_print(p->l);
}
