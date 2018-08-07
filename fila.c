#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"

struct Fila {
    generico* vetor;
    int inicio, fim;
};

#define MAX_ITENS   (1000+1)    // posicao desperdicada na fila circular

Fila* cria(void) {
    Fila* f = malloc(sizeof(Fila));
    f->vetor = malloc(sizeof(generico) * MAX_ITENS);
    f->inicio = f->fim = MAX_ITENS-1;
    return f;
}

void destroi(Fila* f) {
    free(f->vetor);
    free(f);
}

bool underflow(const Fila* f) {
    return f->fim == f->inicio;
}

bool overflow(const Fila* f) {
    /*
    if (f->inicio == 0) {
        return f->fim == MAX_ITENS - 1;
    } else {
        return f->fim == f->inicio - 1;
    }
    */
    return f->fim == ((f->inicio == 0)? (MAX_ITENS - 1): (f->inicio - 1));
}

bool enqueue(Fila* f, generico* g) {
    if (overflow(f)) {
        return false;
    }
    if (f->fim < MAX_ITENS-1) {
        ++f->fim;
    } else {
        f->fim = 0; // retorna ao inicio do vetor para reocupa-lo
    }
    memcpy(f->vetor + f->fim, g, sizeof(generico));
    return true;
}

generico* dequeue(Fila* f) {
    if (underflow(f)) {
        return NULL;
    }
    generico* g = malloc(sizeof(generico));
    if (f->inicio < MAX_ITENS-1) {
        ++f->inicio;
    } else {
        f->inicio = 0;  // retorna ao inicio do vetor para remover dali
    }
    memcpy(g, f->vetor + f->inicio, sizeof(generico));
    return g;
}

void imprime(const Fila* f) {
    if (underflow(f)) {
        printf("(VAZIA)");
        return;
    }
    int i = f->inicio;  // ANTERIOR ao primeiro da fila!
    printf("(INICIO) ");
    do {
        if (i == MAX_ITENS - 1) {
            i = 0;
        } else {
            ++i;
        }
        f->vetor[i].imprime(f->vetor[i].coisa);
        putchar(' ');
    } while (i != f->fim);  // Faz para ateh o fim da fila...
    printf("(FIM)");
}
