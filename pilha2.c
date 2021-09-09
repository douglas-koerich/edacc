#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "pilha.h"
#include "deque.h"

struct pilha {
    deque* d;
};

pilha* create(size_t max) {
    pilha* nova = malloc(sizeof(pilha));
    nova->d = d_create(max);
    return nova;
}

void destroy(pilha* p) {
    if (p == NULL) {
        return;
    }
    d_destroy(p->d);
    free(p);
}

void push(pilha* p, int v) {
    if (p == NULL) {
        return;
    }
    d_insert(p->d, v, FRONT);
}

int pop(pilha* p) {
    if (d_underflow(p->d)) {
        return INT_MIN;
    }
    return d_extract(p->d, FRONT);
}

int top(const pilha* p) {
    if (d_underflow(p->d)) {
        return INT_MIN;
    }
    return d_inspect(p->d, FRONT);
}

size_t size(const pilha* p) {
    if (p == NULL) {
        return 0;
    }
    return d_size(p->d);
}

bool underflow(const pilha* p) {
    if (p == NULL) {
        return true;
    }
    return d_underflow(p->d);
}

void print(const pilha* p) {
    if (p == NULL) {
        return;
    }
    if (d_underflow(p->d)) {
        puts("(VAZIA)");
        return;
    }
    d_print(p->d);
}
