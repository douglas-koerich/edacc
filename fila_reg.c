#include <stdlib.h>
#include <stdio.h>
#include <string.h> // para usar memcpy()
#include "fila_reg.h"

#define TAM_FILA 1024

struct Fila { // customizacao da estrutura de dados original (1o. bim.)
    Reg* vetor;
    int inicio, fim;
};

Fila* cria(void) {
    Fila* f = malloc(sizeof(Fila));
    f->vetor = malloc(sizeof(Reg) * TAM_FILA);
    f->inicio = f->fim = TAM_FILA-1;
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

bool enqueue(Fila* f, const Reg* r) {
    if (overflow(f)) {
        return false;
    }
    if (f->fim == TAM_FILA - 1) {
        f->fim = 0;
    } else {
        ++f->fim;
    }
    memcpy(&f->vetor[f->fim], r, sizeof(Reg));
    return true;
}

bool dequeue(Fila* f, Reg* pc) {
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
    memcpy(pc, &f->vetor[f->inicio], sizeof(Reg));
    return true;
}

void imprime(const Fila* f) {
#ifdef DEBUG
    if (f == NULL) {
        return;
    }
    printf("INICIO >> [");
    if (underflow(f)) {
        printf("**vazia**");
    } else {
        int i = f->inicio;
        do {
            i = i==TAM_FILA-1? 0: i+1;
            printf("%u", f->vetor[i].chave);
            if (i != f->fim) {
                putchar(' ');
            }
        } while (i != f->fim);
    }
    printf("] << FIM\n");
#endif
}

