#include <stdlib.h>
#include <stdio.h>
#include "filaint.h"

int main(void) {
    // int teste[] = { 1, 2, 3, 4, 5, 6, -1 };
    FilaInt* fila = cria();
    print(fila);

    int i;
    for (i=0; /*teste[i] > 0*/ !overflow(fila); ++i) {
        enqueue(fila, /*teste[i]*/ i);
        print(fila);
    }
    if (underflow(fila)) {
        puts("\n\n*****\nVAZIA\n*****\n\n");
    }
    if (overflow(fila)) {
        puts("\n\n*****\nCHEIA\n*****\n\n");
    }
    while (!underflow(fila)) {
        dequeue(fila); // descarta o removido
        print(fila);
    }
    if (underflow(fila)) {
        puts("\n\n*****\nVAZIA\n*****\n\n");
    }
    if (overflow(fila)) {
        puts("\n\n*****\nCHEIA\n*****\n\n");
    }

    destroi(fila);
    return EXIT_SUCCESS;
}

