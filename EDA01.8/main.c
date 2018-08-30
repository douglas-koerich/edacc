#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"  // usuario conhece as interfaces dos TADs fila
#include "fila.h"   // e fila, mas desses headers nao sabe do deque :-)

// Solucao do exercicio 4
void inverte(Fila*);

int main(void) {
    Fila* fila = criaf();
    
    int teste[] = { 0, 1, 1, 2, 3, 5, 8, 1, 13, 21, 1, 34, 55, 1, -1 };
    int i = 0;
    while (teste[i] >= 0 && !overflowf(fila)) {
        enqueuef(fila, teste[i++]);
    }
    printf("Fila original: ");
    imprimef(fila);
    putchar('\n');

    inverte(fila);

    printf("Fila invertida: ");
    imprimef(fila);
    putchar('\n');

    destroif(fila);
    return EXIT_SUCCESS;
}

void inverte(Fila* fila) {
    Pilha* pilha = criap();
    while (!underflowf(fila)) {
        push(pilha, dequeuef(fila));
    }
    while (!underflowp(pilha)) {
        enqueuef(fila, pop(pilha));
    }
    destroip(pilha);
}

