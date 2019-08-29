#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "deque.h"

typedef struct Deque Pilha;

inline extern Pilha* cria_p(void) { // pra nao confundir com a funcao 'cria' da fila
    return (Pilha*) cria();
}
inline extern void destroi_p(Pilha* p) { // idem para 'destroi'
    return destroi((Deque*) p);
}
inline extern bool underflow_p(const Pilha* p) { // ibidem para 'underflow'
    return underflow((const Deque*) p);
}
inline extern bool push(Pilha* p, char c) {
    return enqueue((Deque*) p, c, FIM); // tanto a insercao quanto...
}
inline extern bool pop(Pilha* p, char* pc) {
    return dequeue((Deque*) p, pc, FIM); // ... a remocao sao feitas na mesma extremidade
}

#endif // PILHA_H

