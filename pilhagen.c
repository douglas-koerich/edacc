#include <stdio.h>
#include <string.h> // declaracao de memcpy
#include "pilhagen.h"

// Definicao "efetiva" da estrutura que implementa o TAD pilha
// na memoria
struct pilha {
    Tipo* vetor; // alocado dinamicamente quando souber o tamanho em cria()
    int topo; // indice da extremidade com acesso permitido para E/S da pilha
    size_t tamanho; // necessario para comparacao da pilha cheia
};

Pilha* cria(size_t tamanho) {
    Pilha* p = malloc(sizeof(struct pilha)); // aloca o par de campos
    p->vetor = malloc(tamanho * sizeof(Tipo)); // aloca o vetor de tamanho
                                               // (agora) conhecido
    p->topo = -1; // se fosse 0 seria uma indicacao de que existe um elemento
                  // armazenado no inicio do vetor, entao marca como -1
    p->tamanho = tamanho;
    return p;
}

bool underflow(const Pilha* p) {
    return p->topo == -1;
}

bool overflow(const Pilha* p) {
    return p->topo == p->tamanho - 1; // topo no ultimo indice do vetor?
}

void destroi(Pilha* p) {
    free(p->vetor); // libera vetor antes, senao perde o endereco dele!
    free(p);
}

void dump(const Pilha* p) {
    printf("(BASE) ");
    int i;
    for (i=0; i<=p->topo; ++i) { // para todos os indices validos do vetor
        unsigned char* pbyte = &p->vetor[i]; // endereco do primeiro byte do tipo
        int b;
        printf("{ ");
        for (b=0; b<sizeof(Tipo); ++b, ++pbyte) { // para cada um dos bytes do tipo...
            printf("%02hhX ", *pbyte); // ... imprime o byte da vez em hexa
        }
        printf("} ");
    }
    printf("(TOPO)");
}

void push(Pilha* p, const Tipo* v) {
    if (overflow(p)) {
        fprintf(stderr, "Pilha cheia!\n");
        return;
    }
    ++p->topo;
    memcpy(&p->vetor[p->topo], v, sizeof(Tipo));
}

void pop(Pilha* p, Tipo* v) {
    if (underflow(p)) {
        fprintf(stderr, "Pilha vazia, IGNORE *v!\n");
        return;
    }
    memcpy(v, &p->vetor[p->topo], sizeof(Tipo));
    --p->topo;
}

