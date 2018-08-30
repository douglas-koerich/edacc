#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

// Uso analogo ao que foi ilustrado no exercicio 1
int main(void) {
    Fila* fila = cria();

    int teste[] = { 1, 2, 3, 5, 8, 13, -1 }; // fibonacci
    int i = 0;
    while (teste[i] > 0 && !overflow(fila)) {
        enqueue(fila, teste[i]);
        
        printf("Fila atual: ");
        imprime(fila);
        
        printf(" (tamanho = %zd)\n", tamanho(fila));

        ++i;
    }
    destroi(fila);

    return EXIT_SUCCESS;
}

