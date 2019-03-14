#include <stdio.h>
#include <string.h> // declaracao de memcpy
#include "filagen.h"

// Definicao "efetiva" da estrutura que implementa o TAD fila
// na memoria
struct fila {
    Tipo* vetor; // alocado dinamicamente quando souber o tamanho em cria()
    int inicio; // indice da extremidade com acesso permitido para SAIDA da fila
    int fim;    // indice da extremidade com acesso permitido para ENTRADA na fila
    size_t tamanho; // necessario para comparacao da fila cheia
};

Fila* cria(size_t tamanho) {
    Fila* f = malloc(sizeof(struct fila)); // aloca o par de campos

    ++tamanho; // reserva uma posicao EXTRA para o controle de overflow
               // da fila circular
    f->vetor = malloc(tamanho * sizeof(Tipo)); // aloca o vetor de tamanho
                                               // (agora) conhecido
    f->inicio = f->fim = tamanho-1; // inicia na ultima posicao do vetor
    f->tamanho = tamanho;
    return f;
}

bool underflow(const Fila* f) {
    return f->inicio == f->fim;
}

bool overflow(const Fila* f) {
    if (f->inicio == 0) {
        return f->fim == f->tamanho - 1;
    } else {
        return f->fim == f->inicio - 1;
    }
}

void destroi(Fila* f) {
    free(f->vetor); // libera vetor antes, senao perde o endereco dele!
    free(f);
}

void dump(const Fila* f) {
    printf("(INICIO) ");
    int i = f->inicio;
    while (i != f->fim) {
        if (i == f->tamanho - 1) {
            i = 0;
        } else {
            ++i;
        }
        unsigned char* pbyte = (unsigned char*) &f->vetor[i]; // endereco do primeiro byte do tipo
        int b;
        printf("{ ");
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("} ");
    }
    printf("(FIM)");
}

void enqueue(Fila* f, const Tipo* v) {
    if (overflow(f)) {
        fprintf(stderr, "Fila cheia!\n");
        return;
    }
    if (f->fim == f->tamanho-1) {
        f->fim = 0;
    } else {
        ++f->fim;
    }
    memcpy(&f->vetor[f->fim], v, sizeof(Tipo));
}

void dequeue(Fila* f, Tipo* v) {
    if (underflow(f)) {
        fprintf(stderr, "Fila vazia, IGNORE *v!\n");
        return;
    }
    if (f->inicio == f->tamanho-1) {
        f->inicio = 0;
    } else {
        ++f->inicio;
    }
    memcpy(v, &f->vetor[f->inicio], sizeof(Tipo));
}

