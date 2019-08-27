#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

#define TAM_FILA 1024

struct Fila {
    char* vetor; // vetor alocado dinamicamente
    int inicio;  // indice de referencia para remocao
    int fim;     // indice de referencia para insercao
};

Fila* cria(void) {
    Fila* f = malloc(sizeof(Fila));
    f->vetor = malloc(sizeof(char) * TAM_FILA);
    f->inicio = f->fim = TAM_FILA-1; // ultimo indice
    return f;
}

void destroi(Fila* f) {
    if (f == NULL) {
        return;
    }
    free(f->vetor);
    free(f);
}

bool underflow(const Fila* f) {
    if (f == NULL) {
        return false;
    }
    return f->inicio == f->fim;
}

bool overflow(const Fila* f) {
    if (f == NULL) {
        return false;
    }
    if (f->inicio == 0) {
        return f->fim == TAM_FILA - 1;
    }
    return f->fim == f->inicio - 1;
}

bool enqueue(Fila* f, char c) {
    if (overflow(f)) {
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
    if (underflow(f)) {
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
void imprime(const Fila* f) {
    if (f == NULL) {
        return;
    }
    printf("\nINICIO >> [");
    if (underflow(f)) {
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

