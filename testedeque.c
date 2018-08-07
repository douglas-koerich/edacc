#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dequeint.h"

void print(DequeInt* d) {
    putchar('\n');
    print_d(d);
    putchar('\n');
}

int main(void) {
    DequeInt* deque = cria_d();
    print(deque);

    int i;
    for (i=0; !overflow_d(deque); ++i) {
        if (i%2==0) {
            enqueue_d(deque, DIREITO, i);
        } else {
            enqueue_d(deque, ESQUERDO, i);
        }
        print(deque);
    }
    if (underflow_d(deque)) {
        puts("\n\n*****\nVAZIO\n*****\n\n");
    }
    if (overflow_d(deque)) {
        puts("\n\n*****\nCHEIO\n*****\n\n");
    }
    while (!underflow_d(deque)) {
        char lado;
        do {
            printf("Digite o lado a remover (E/D): ");
            scanf(" %c", &lado);
            lado = toupper(lado);
        } while (lado != 'E' && lado != 'D');
        dequeue_d(deque, lado=='E'? ESQUERDO: DIREITO);
        print(deque);
    }
    if (underflow_d(deque)) {
        puts("\n\n*****\nVAZIO\n*****\n\n");
    }
    if (overflow_d(deque)) {
        puts("\n\n*****\nCHEIO\n*****\n\n");
    }

    destroi_d(deque);
    return EXIT_SUCCESS;
}

