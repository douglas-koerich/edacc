#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"
#include "deque.h" // uso "escondido" do deque

struct Pilha {
    Deque* impl;
};

Pilha* criap(void) {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->impl = cria(); // cria o deque subjacente
    return nova;
}

void destroip(Pilha* pilha) {
    destroi(pilha->impl);   // destroi o deque subjacente
    free(pilha);
}

void imprimep(const Pilha* pilha) {
    imprime(pilha->impl); // imprime o deque subjacente
}

bool underflowp(const Pilha* pilha) {
    return underflow(pilha->impl);
}

bool overflowp(const Pilha* pilha) {
    return overflow(pilha->impl);
}

void push(Pilha* pilha, int valor) {
    enqueue(pilha->impl, valor, TRAS);
}

int pop(Pilha* pilha) {
    return dequeue(pilha->impl, TRAS);  // MESMO extremo do push()!!!
}

