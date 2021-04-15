#include "pilha.h"
#include "fila.h"
#include "deque.h"

void push(Pilha* a_pilha, TipoElemento novo_elemento) {
    d_enqueue((Deque*) a_pilha, novo_elemento, FIM);
}

TipoElemento pop(Pilha* a_pilha) {
    return d_dequeue((Deque*) a_pilha, FIM);
}

void enqueue(Fila* a_fila, TipoElemento novo_elemento) {
    d_enqueue((Deque*) a_fila, novo_elemento, FIM);
}

TipoElemento dequeue(Fila* a_fila) {
    return d_dequeue((Deque*) a_fila, INICIO);
}
