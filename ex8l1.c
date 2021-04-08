#include <stdlib.h>
#include <stdio.h>

#include "elemento.h"
#include "fila.h"
#include "pilha.h"

void inverte(Fila*);

int main(void) {
    Fila* amostra = f_create();

    int i;
    for (i = 1; i <= 10; ++i) {
        TipoElemento x = rand() % 100 + 1;
        enqueue(amostra, x);
    }
    puts("Antes da inversao (fila original):");
    f_print(amostra);

    inverte(amostra);

    puts("Depois da inversao:");
    f_print(amostra);

    f_destroy(amostra);

    return EXIT_SUCCESS;
}

void inverte(Fila* uma_fila) {
    Pilha* apoio = p_create();

    while (!f_underflow(uma_fila)) {
        // Retira da fila (dequeue) e poe direto na pilha (push)
        push(apoio, dequeue(uma_fila));
    }

    while (!p_underflow(apoio)) {
        // Retira da pilha (pop) e poe de volta na fila (enqueue)
        enqueue(uma_fila, pop(apoio));
    }

    p_destroy(apoio);
}