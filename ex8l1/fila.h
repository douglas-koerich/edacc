#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "deque.h"

typedef struct Deque Fila;

// Funcoes inline extern tem o seu codigo substituido na chamada
// original, e nao uma chamada convencional para a funcao
inline extern Fila* cria_f(void) {
    return (Fila*) cria_d(); // chama cria() do Deque, usa cast pra mudar o tipo
}
inline extern void destroi_f(Fila* f) {
    destroi_d((Deque*) f);   // o cast aqui serve pra "lembrar" que sempre tive um Deque*
}
inline extern bool underflow_f(const Fila* f) {
    return underflow_d((const Deque*) f);
}
inline extern bool enqueue_f(Fila* f, char c) {
    return enqueue_d((Deque*) f, c, FIM); // chama enqueue() do deque para o caso classico
}
inline extern bool dequeue_f(Fila* f, char* pc) {
    return dequeue_d((Deque*) f, pc, INICIO); // chama dequeue() para o caso classico
}

// EXTRA
inline extern bool overflow_f(const Fila* f) {
    return overflow_d((const Deque*) f);
}
#ifdef DEBUG
inline extern void imprime_f(const Fila* f) {
    imprime_d((const Deque*) f);
}
#endif

#endif // FILA_H
