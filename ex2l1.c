#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

void transfere(Pilha*, Pilha*);

int main(void) {
    srand(2021);

    // Cria pilhas para teste
    Pilha* S1 = create();
    Pilha* S2 = create();

    // Preenche a pilha S1 com alguns numeros aleatorios
    int i;
    for (i = 1; i <= 5; ++i) {
        push(S1, rand() % 100);
    }

    // Imprime o conteudo das pilhas para conferencia
    puts("Pilha S1");
    print(S1);
    puts("\nPilha S2");
    print(S2);

    transfere(S2, S1); // move os elementos de S1 para S2

    // Imprime o conteudo das pilhas novamente
    puts("\nPilha S1");
    print(S1);
    puts("\nPilha S2");
    print(S2);

    // Finaliza destruindo as pilhas criadas
    destroy(S1);
    destroy(S2);

    return EXIT_SUCCESS;
}

void transfere(Pilha* destino, Pilha* origem) {
    Pilha* apoio = create();

    while (!underflow(origem)) {
        int valor = pop(origem);
        push(apoio, valor);
    }

    // Imprime para visualizar o processo
    puts("\nPilha de apoio");
    print(apoio);

    while (!underflow(apoio)) {
        push(destino, pop(apoio));
    }

    destroy(apoio);
}