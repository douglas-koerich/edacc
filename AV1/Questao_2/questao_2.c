#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

/* A PROXIMA FUNCAO EH UMA RESPOSTA DA QUESTAO 2 */

FilaInt* divide_ao_meio(FilaInt* original) {
    FilaInt* nova = criar();
    unsigned contador = 0;
    while (!underflow(original)) {
        enqueue(nova, dequeue(original));
        ++contador;
    }
    contador = contador / 2;
    while (contador > 0) {
        enqueue(original, dequeue(nova));
        --contador;
    }
    return nova;
}

/* A FUNCAO main() //NAO// EH PARTE DA SOLUCAO DA QUESTAO 2, ESTAH AQUI APENAS
   PARA DEMONSTRACAO */

int main() {
    int sequencia[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, -1 };

    FilaInt* fila = criar();
    int i = 0;
    while (sequencia[i] > 0) {
        if (overflow(fila) == false) {
            enqueue(fila, sequencia[i]);
        }
        ++i;
    }
    printf("Fila original: ");
    imprimir(fila);

    FilaInt* metade = divide_ao_meio(fila);

    printf("\nFila original: ");
    imprimir(fila);
    printf("\nFila nova: ");
    imprimir(metade);
    putchar('\n');

    destruir(fila);
    destruir(metade);
    return EXIT_SUCCESS;
}
