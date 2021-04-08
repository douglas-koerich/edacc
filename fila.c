#include <stdio.h>
#include "fila.h"

#define TAM_MAX_FILA 100

struct fila {
    TipoElemento* vetor; // diferente da pilha, aqui vamos alocar dinamicamente
    int inicio, fim; // dois indices de controle das extremidades da fila
                     // dentro do vetor
};

void enqueue(Fila* a_fila, TipoElemento novo_elemento) {
    if (a_fila->inicio == 0 && a_fila->fim == TAM_MAX_FILA - 1 ||
        a_fila->fim == a_fila->inicio - 1) {
        puts("ERRO: fila cheia!");
        return;
    }
    a_fila->vetor[a_fila->fim] = novo_elemento;
    if (++a_fila->fim == TAM_MAX_FILA) {
        a_fila->fim = 0;
    }
}

TipoElemento dequeue(Fila* a_fila) {
    if (underflow(a_fila)) {
        puts("ERRO: fila vazia!");
        destroy((Fila*) a_fila); // remove o modo constante do ponteiro
        exit(EXIT_FAILURE);
    }
    TipoElemento e = a_fila->vetor[a_fila->inicio];
    if (++a_fila->inicio == TAM_MAX_FILA) {
        a_fila->inicio = 0;
    }
}

TipoElemento front(const Fila* a_fila) {
    if (underflow(a_fila)) {
        puts("ERRO: fila vazia!");
        destroy((Fila*) a_fila);
        exit(EXIT_FAILURE);
    }
    return a_fila->vetor[a_fila->inicio];
}

TipoElemento rear(const Fila* a_fila) {
    if (underflow(a_fila)) {
        puts("ERRO: fila vazia!");
        destroy((Fila*) a_fila);
        exit(EXIT_FAILURE);
    }
    int ultimo;
    if (a_fila->fim == 0) {
        ultimo = TAM_MAX_FILA - 1;
    } else {
        ultimo = a_fila->fim - 1;
    }
    return a_fila->vetor[ultimo];
}

size_t size(const Fila* a_fila) {
    if (a_fila->fim >= a_fila->inicio) {
        return a_fila->fim - a_fila->inicio;
    } else {
        return TAM_MAX_FILA + a_fila->fim - a_fila->inicio;
    }
}

bool underflow(const Fila* a_fila) {
    return a_fila->inicio == a_fila->fim;
}

Fila* create(void) {
    Fila* nova = malloc(sizeof(Fila));
    nova->vetor = malloc(sizeof(TipoElemento) * TAM_MAX_FILA);
    nova->inicio = 0; // primeira posicao a ser ocupada por uma insercao
    nova->fim = 0; // primeira posicao livre (para insercao) no vetor
    return nova;
}

void destroy(Fila* a_fila) {
    free(a_fila->vetor); // agora eh preciso liberar tambem o vetor pois
                         // ele foi alocado dinamicamente
    free(a_fila);
}

void print(const Fila* a_fila) {
    printf("(INICIO) ");
    int pos = a_fila->inicio;
    while (pos != a_fila->fim) {
        printf("%d ", a_fila->vetor[pos++]);
        if (pos == TAM_MAX_FILA) {
            pos = 0;
        }
    }
    puts("(FIM)");
}
