#include <stdio.h>
#include <string.h> // declaracao de memcpy
#include "dequegen.h"

// Definicao "efetiva" da estrutura que implementa o TAD deque
// na memoria
struct deque {
    Tipo* vetor; // alocado dinamicamente quando souber o tamanho em cria()
    int inicio; // indice da extremidade com acesso permitido para SAIDA do deque
    int fim;    // indice da extremidade com acesso permitido para ENTRADA no deque
    size_t tamanho; // necessario para comparacao do deque cheio
};

Deque* cria_d(size_t tamanho) {
    Deque* d = malloc(sizeof(struct deque)); // aloca o par de campos

    ++tamanho; // reserva uma posicao EXTRA para o controle de overflow
               // do deque circular
    d->vetor = malloc(tamanho * sizeof(Tipo)); // aloca o vetor de tamanho
                                               // (agora) conhecido
    d->inicio = d->fim = tamanho-1; // inicia na ultima posicao do vetor
    d->tamanho = tamanho;
    return d;
}

bool underflow_d(const Deque* d) {
    return d->inicio == d->fim;
}

bool overflow_d(const Deque* d) {
    if (d->inicio == 0) {
        return d->fim == d->tamanho - 1;
    } else {
        return d->fim == d->inicio - 1;
    }
}

void destroi_d(Deque* d) {
    free(d->vetor); // libera vetor antes, senao perde o endereco dele!
    free(d);
}

void dump_d(const Deque* d) {
    printf("(INICIO) ");
    int i = d->inicio;
    while (i != d->fim) {
        if (i == d->tamanho - 1) {
            i = 0;
        } else {
            ++i;
        }
        unsigned char* pbyte = (unsigned char*) &d->vetor[i]; // endereco do primeiro byte do tipo
        int b;
        printf("{ ");
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("} ");
    }
    printf("(FIM)");
}

void enqueue_d(Deque* d, const Tipo* v, Lado l) {
    if (overflow_d(d)) {
        fprintf(stderr, "Deque cheio!\n");
        return;
    }
    if (l == FIM) {
        // Implementacao da insercao no TAD 'Fila' original
        if (d->fim == d->tamanho-1) {
            d->fim = 0;
        } else {
            ++d->fim;
        }
        memcpy(&d->vetor[d->fim], v, sizeof(Tipo));
    } else {
        // Nova modalidade de insercao, no INICIO do deque
        memcpy(&d->vetor[d->inicio], v, sizeof(Tipo)); // 'inicio' estah na posicao livre
                                                       // anterior ah "cabeca" atual do deque
        if (d->inicio == 0) {
            d->inicio = d->tamanho - 1;
        } else {
            --d->inicio;
        }
    }
}

void dequeue_d(Deque* d, Tipo* v, Lado l) {
    if (underflow_d(d)) {
        fprintf(stderr, "Deque vazio, IGNORE *v!\n");
        return;
    }
    if (l == INICIO) {
        // Implementacao da remocao do TAD 'Fila' original
        if (d->inicio == d->tamanho-1) {
            d->inicio = 0;
        } else {
            ++d->inicio;
        }
        memcpy(v, &d->vetor[d->inicio], sizeof(Tipo));
    } else {
        // Nova modalidade de remocao, do FIM do deque
        memcpy(v, &d->vetor[d->fim], sizeof(Tipo));
        if (d->fim == 0) {
            d->fim = d->tamanho - 1;
        } else {
            --d->fim;
        }
    }
}

