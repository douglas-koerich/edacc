#include <stdio.h>
#include "pilha.h"

#define TAM_MAX_PILHA 100

// Implementacao usando um VETOR como espaco de armazenamento e
// acesso aleatorio (embora desnecessario, pois soh vai usar o topo)
struct pilha {
    TipoElemento vetor[TAM_MAX_PILHA];
    int topo; // neste caso, marca a posicao do vetor em que estah
              // localizado o ultimo-que-entrou/primeiro-a-sair (LIFO)
};

void push(Pilha* a_pilha, TipoElemento novo_elemento) {
    if (a_pilha->topo == TAM_MAX_PILHA - 1) {
        puts("ERRO: pilha cheia!");
        return;
    }
    /*
    ++a_pilha->topo; // avanca para a proxima posicao livre
    a_pilha->vetor[a_pilha->topo] = novo_elemento; // novo topo da pilha
    */
    a_pilha->vetor[++a_pilha->topo] = novo_elemento;
}

TipoElemento pop(Pilha* a_pilha) {
    if (underflow(a_pilha)) {
        puts("ERRO: pilha vazia!");
        destroy(a_pilha);
        exit(EXIT_FAILURE);
    }
    /*
    TipoElemento e = a_pilha->vetor[a_pilha->topo];
    --a_pilha->topo;
    return e;
    */
    return a_pilha->vetor[a_pilha->topo--];
}

TipoElemento top(const Pilha* a_pilha) {
    if (underflow(a_pilha)) {
        puts("ERRO: pilha vazia!");
        destroy((Pilha*) a_pilha); // remove o modo constante do ponteiro
        exit(EXIT_FAILURE);
    }
    return a_pilha->vetor[a_pilha->topo];
}

size_t size(const Pilha* a_pilha) {
    return a_pilha->topo + 1;
}

bool underflow(const Pilha* a_pilha) {
    return a_pilha->topo == -1;
}

Pilha* create(void) {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->topo = -1; // indice invalido, nenhum elemento estah no topo
    return nova;
}

void destroy(Pilha* a_pilha) {
    free(a_pilha);
}

// Outras operacoes auxiliares
void print(const Pilha* a_pilha) {
    puts("(TOPO)");
    int i = a_pilha->topo;
    while (i >= 0) {
        printf("%#x\n", a_pilha->vetor[i--]);
    }
    puts("(BASE)");
}
