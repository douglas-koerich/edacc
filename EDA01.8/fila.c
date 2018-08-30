#include <stdlib.h>
#include <stdio.h>
#include "fila.h"
#include "deque.h" // uso "escondido" do deque

struct Fila {
    Deque* impl;
};

Fila* criaf(void) {
    Fila* nova = malloc(sizeof(Fila));
    nova->impl = cria(); // cria o deque subjacente
    return nova;
}

void destroif(Fila* fila) {
    destroi(fila->impl);   // destroi o deque subjacente
    free(fila);
}

void imprimef(const Fila* fila) {
    imprime(fila->impl); // imprime o deque subjacente
}

bool underflowf(const Fila* fila) {
    return underflow(fila->impl);
}

bool overflowf(const Fila* fila) {
    return overflow(fila->impl);
}

void enqueuef(Fila* fila, int valor) {
    enqueue(fila->impl, valor, TRAS);
}

int dequeuef(Fila* fila) {
    return dequeue(fila->impl, FRENTE);  // extremo OPOSTO do enqueuef()!!!
}

