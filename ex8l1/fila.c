#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

#define TAM_FILA 1024

struct Fila {
    char* vetor;
    int inicio, fim;
};

Fila* cria_f(void) {
    Fila* f = malloc(sizeof(Fila));
    f->vetor = malloc(sizeof(char) * TAM_FILA);
    f->inicio = f->fim = TAM_FILA-1;
    return f;
}

void destroi_f(Fila* f) {
    if (f == NULL) {
        return;
    }
    free(f->vetor);
    free(f);
}

bool underflow_f(const Fila* f) {
    if (f == NULL) {
        return false;
    }
    return f->inicio == f->fim;
}

bool overflow_f(const Fila* f) {
    if (f == NULL) {
        return false;
    }
    if (f->inicio == 0) {
        return f->fim == TAM_FILA - 1;
    }
    return f->fim == f->inicio - 1;
}

bool enqueue(Fila* f, char c) {
    if (overflow_f(f)) {
        return false;
    }
    if (f->fim == TAM_FILA - 1) {
        f->fim = 0;
    } else {
        ++f->fim;
    }
    f->vetor[f->fim] = c;
    return true;
}

bool dequeue(Fila* f, char* pc) {
    if (underflow_f(f)) {
        return false;
    }
    if (pc == NULL) {
        return false;
    }
    if (f->inicio == TAM_FILA - 1) {
        f->inicio = 0;
    } else {
        ++f->inicio;
    }
    *pc = f->vetor[f->inicio];
    return true;
}

#ifdef DEBUG
void imprime_f(const Fila* f) {
    if (f == NULL) {
        return;
    }
    printf("\nINICIO >> [");
    if (underflow_f(f)) {
        printf("**vazia**");
    } else {
        int i = f->inicio;
        do {
            i = i==TAM_FILA-1? 0: i+1;
            putchar(f->vetor[i]);
            if (i != f->fim) {
                putchar(' ');
            }
        } while (i != f->fim);
    }
    printf("] << FIM\n");
}
#endif

