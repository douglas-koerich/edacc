#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(void) {
    Pilha* pilha = cria();

    int teste[] = { 1, 2, 3, 5, 8, 13, -1 }; // fibonacci
    int i = 0;
    while (teste[i] > 0 && !overflow(pilha)) {
        push(pilha, teste[i]);
        
        printf("Pilha atual: ");
        imprime(pilha);
        
        printf(" (tamanho = %zd)\n", tamanho(pilha));

        ++i;
    }
    destroi(pilha);

    return EXIT_SUCCESS;
}

