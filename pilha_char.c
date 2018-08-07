#include <stdlib.h>
#include "pilha_char.h"

struct Pilha_ch {
    char vetor[MAX_ELEMENTOS_PILHA];
    int topo;
};

Pilha_ch* cria(void) {
    Pilha_ch* p = (Pilha_ch*) malloc(sizeof(Pilha_ch));
    p->topo = -1;
    return p;
}
void destroi(Pilha_ch* p) {
    free(p);
}
bool underflow(const Pilha_ch* p) {
    return p->topo == -1;
}
bool overflow(const Pilha_ch* p) {
    return p->topo == MAX_ELEMENTOS_PILHA-1;
}
void push(Pilha_ch* p, char c) {
    p->vetor[++p->topo] = c;
}
char pop(Pilha_ch* p) {
    return p->vetor[p->topo--];
}
