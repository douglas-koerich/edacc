#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

void inverte(Pilha*);

int main(void) {
    srand(2021);

    // Cria pilha para teste
    Pilha* S = create();

    // Preenche a pilha S1 com alguns numeros aleatorios
    int i;
    for (i = 1; i <= 5; ++i) {
        push(S, rand() % 100);
    }

    // Imprime o conteudo da pilha para conferencia
    puts("Pilha S");
    print(S);

    inverte(S);

    // Imprime o conteudo da pilha novamente
    puts("\nPilha S");
    print(S);

    // Finaliza destruindo a pilha criada
    destroy(S);

    return EXIT_SUCCESS;
}

void inverte(Pilha* p) {
    Pilha* apoio1 = create();
    Pilha* apoio2 = create();

    while (!underflow(p)) {
        int valor = pop(p);
        push(apoio1, valor);
    }

    while (!underflow(apoio1)) {
        push(apoio2, pop(apoio1));
    }

    while (!underflow(apoio2)) {
        push(p, pop(apoio2));
    }

    destroy(apoio1);
    destroy(apoio2);
}