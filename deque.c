#include <stdio.h>
#include "deque.h"

#define TAM_MAX_FILA 100

struct deque {
    TipoElemento* vetor;
    int inicio, fim;
};

void d_enqueue(Deque* o_deque, TipoElemento novo_elemento, Lado onde) {
    if (o_deque->inicio == 0 && o_deque->fim == TAM_MAX_FILA - 1 ||
        o_deque->fim == o_deque->inicio - 1) {
        puts("ERRO: fila cheia!");
        return;
    }
    if (onde == FIM) {
        // Implementacao original da fila
        o_deque->vetor[o_deque->fim] = novo_elemento;
        if (++o_deque->fim == TAM_MAX_FILA) {
            o_deque->fim = 0;
        }
    } else { // insercao no INICIO
        if (--o_deque->inicio < 0) {
            o_deque->inicio = TAM_MAX_FILA - 1;
        }
        o_deque->vetor[o_deque->inicio] = novo_elemento;
    }
}

TipoElemento d_dequeue(Deque* o_deque, Lado onde) {
    if (d_underflow(o_deque)) {
        puts("ERRO: fila vazia!");
        d_destroy((Deque*) o_deque);
        exit(EXIT_FAILURE);
    }
    TipoElemento e;
    if (onde == INICIO) {
        // Implementacao original da fila
        e = o_deque->vetor[o_deque->inicio];
        if (++o_deque->inicio == TAM_MAX_FILA) {
            o_deque->inicio = 0;
        }
    } else { // remocao do FIM
        if (--o_deque->fim < 0) {
            o_deque->fim = TAM_MAX_FILA - 1;
        }
        e = o_deque->vetor[o_deque->fim];
    }
    return e;
}

TipoElemento d_front(const Deque* o_deque) {
    if (d_underflow(o_deque)) {
        puts("ERRO: fila vazia!");
        d_destroy((Deque*) o_deque);
        exit(EXIT_FAILURE);
    }
    return o_deque->vetor[o_deque->inicio];
}

TipoElemento d_rear(const Deque* o_deque) {
    if (d_underflow(o_deque)) {
        puts("ERRO: fila vazia!");
        d_destroy((Deque*) o_deque);
        exit(EXIT_FAILURE);
    }
    int ultimo;
    if (o_deque->fim == 0) {
        ultimo = TAM_MAX_FILA - 1;
    } else {
        ultimo = o_deque->fim - 1;
    }
    return o_deque->vetor[ultimo];
}

size_t d_size(const Deque* o_deque) {
    if (o_deque->fim >= o_deque->inicio) {
        return o_deque->fim - o_deque->inicio;
    } else {
        return TAM_MAX_FILA + o_deque->fim - o_deque->inicio;
    }
}

bool d_underflow(const Deque* o_deque) {
    return o_deque->inicio == o_deque->fim;
}

Deque* d_create(void) {
    Deque* novo = malloc(sizeof(Deque));
    novo->vetor = malloc(sizeof(TipoElemento) * TAM_MAX_FILA);
    novo->inicio = 0;
    novo->fim = 0;
    return novo;
}

void d_destroy(Deque* o_deque) {
    free(o_deque->vetor); // agora eh preciso liberar tambem o vetor pois
                         // ele foi alocado dinamicamente
    free(o_deque);
}

void d_print(const Deque* o_deque) {
    printf("(INICIO) ");
    int pos = o_deque->inicio;
    while (pos != o_deque->fim) {
        printf("%d ", o_deque->vetor[pos++]);
        if (pos == TAM_MAX_FILA) {
            pos = 0;
        }
    }
    puts("(FIM)");
}
