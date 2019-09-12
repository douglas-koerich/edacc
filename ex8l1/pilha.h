#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "deque.h"

typedef struct Deque Pilha;

inline extern Pilha* cria_p(void) { // pra nao confundir com a funcao 'cria' da fila
    return (Pilha*) cria_d();
}
inline extern void destroi_p(Pilha* p) { // idem para 'destroi'
    return destroi_d((Deque*) p);
}
inline extern bool underflow_p(const Pilha* p) { // ibidem para 'underflow'
    return underflow_d((const Deque*) p);
}
inline extern bool push(Pilha* p, char c) {
    return enqueue_d((Deque*) p, c, FIM); // tanto a insercao quanto...
}
inline extern bool pop(Pilha* p, char* pc) {
    return dequeue_d((Deque*) p, pc, FIM); // ... a remocao sao feitas na mesma extremidade
}

#endif // PILHA_H

