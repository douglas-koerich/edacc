#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(void) {
    int sequencia[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, -1 };

    // Cria pilha para inverter a sequencia
    pilha* p = create(20);
    int i = 0;
    printf("Sequencia direta: ");
    while (sequencia[i] != -1) {
        printf("%d ", sequencia[i]);
        push(p, sequencia[i]);
        ++i;
    }
    putchar('\n');

    puts("Conteudo da pilha:");
    print(p);
    putchar('\n');

    // Obtem a sequencia inversa da original
    printf("Sequencia inversa: ");
    while (underflow(p) == false) { // enquanto pilha nao estiver vazia
        i = pop(p);
        printf("%d ", i);
    }
    putchar('\n');

    destroy(p);

    return EXIT_SUCCESS;
}