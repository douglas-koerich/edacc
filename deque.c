#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "deque.h"

struct Deque {
    generico* vetor;
    int inicio, fim;
};

#define MAX_ITENS   (1000+1)    // posicao desperdicada no deque circular

Deque* cria(void) {
    Deque* d = malloc(sizeof(Deque));
    d->vetor = malloc(sizeof(generico) * MAX_ITENS);
    d->inicio = d->fim = MAX_ITENS-1;
    return d;
}

void destroi(Deque* d) {
    free(d->vetor);
    free(d);
}

bool underflow(const Deque* d) {
    return d->fim == d->inicio;
}

bool overflow(const Deque* d) {
    /*
    if (d->inicio == 0) {
        return d->fim == MAX_ITENS - 1;
    } else {
        return d->fim == d->inicio - 1;
    }
    */
    return d->fim == ((d->inicio == 0)? (MAX_ITENS - 1): (d->inicio - 1));
}

bool enqueue(Deque* d, Extremidade e, generico* g) {
    if (overflow(d)) {
        return false;
    }
    if (e == FIM) {
        if (d->fim < MAX_ITENS-1) {
            ++d->fim;
        } else {
            d->fim = 0; // retorna ao inicio do vetor para reocupa-lo
        }
        memcpy(d->vetor + d->fim, g, sizeof(generico));
    } else {
        memcpy(d->vetor + d->inicio, g, sizeof(generico));
        if (d->inicio > 0) {
            --d->inicio;
        } else {
            d->inicio = MAX_ITENS-1;
        }
    }
    return true;
}

generico* dequeue(Deque* d, Extremidade e) {
    if (underflow(d)) {
        return NULL;
    }
    generico* g = malloc(sizeof(generico));
    if (e == INICIO) {
        if (d->inicio < MAX_ITENS-1) {
            ++d->inicio;
        } else {
            d->inicio = 0;  // retorna ao inicio do vetor para remover dali
        }
        memcpy(g, d->vetor + d->inicio, sizeof(generico));
    } else {
        memcpy(g, d->vetor + d->fim, sizeof(generico));
        if (d->fim > 0) {
            --d->fim;
        } else {
            d->fim = MAX_ITENS-1;
        }
    }
    return g;
}

void imprime(const Deque* d) {
    if (underflow(d)) {
        printf("(VAZIO)");
        return;
    }
    int i = d->inicio;  // ANTERIOR ao primeiro do deque!
    printf("(INICIO) ");
    do {
        if (i == MAX_ITENS - 1) {
            i = 0;
        } else {
            ++i;
        }
        d->vetor[i].imprime(d->vetor[i].coisa);
        putchar(' ');
    } while (i != d->fim);  // Faz para ateh o fim do deque...
    printf("(FIM)");
}
