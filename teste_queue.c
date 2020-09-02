#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#define MAX 100

int main(void) {
    Queue* fila = create(MAX);

    int contador = 0, entrada;
    do {
        printf("Digite uma novo numero inteiro para teste, ou -1 para terminar: ");
        scanf("%d", &entrada);
        if (entrada != -1) {
            if (!enqueue(fila, entrada)) {
                puts("ERRO NO ENFILEIRAMENTO");
                break;
            }
        }
        ++contador;
    } while (entrada != -1 && contador < MAX);

    puts("Conteudo da fila agora:");
    print(fila);
    putchar('\n');

    printf("O numero no inicio da fila eh %d\n", front(fila));
    printf("O numero no fim da fila eh %d\n", rear(fila));

    while (!underflow(fila)) {
        dequeue(fila);
        if (!underflow(fila)) {
            printf("Agora o inicio eh %d\n", front(fila));
        }
    }    

    destroy(fila);

    return EXIT_SUCCESS;
}