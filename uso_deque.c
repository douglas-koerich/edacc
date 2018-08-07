#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "tad_deque_inteiros.h"

/* Construa um deque com numeros aleatorios (1-100) da seguinte maneira: pares sao
 * adicionados no fim do deque, enquanto impares sao inseridos no inicio (interrompa
 * se o numero gerado for nulo)... Em seguida, solicite ao usuario que escolha a
 * remocao de um dos extremos do deque, e repita essa operacao enquanto houver
 * numeros no deque e o usuario escolher uma extremidade valida. */

int main(void) {
    srand((unsigned) time(NULL));

    DequeInt* deque = cria_deque();
    int n;
    do {
        n = rand() % 101;
        if (n > 0) {
            if (n % 2 == 0) {
                d_enqueue(deque, n, FIM);
            } else {
                d_enqueue(deque, n, INICIO);
            }
        }
    } while (n > 0 && !doverflow(deque));

    puts("Deque gerado:");
    imprime_deque(deque);
    putchar('\n');

    while (!dunderflow(deque)) {
        char lado;
        printf("Digite um lado para remover (I/F): ");
        scanf(" %c", &lado);
        lado = toupper(lado);
        if (lado == 'I') {
            d_dequeue(deque, INICIO);
        } else if (lado == 'F') {
            d_dequeue(deque, FIM);
        } else {
            break;
        }
        puts("Deque apos remocao:");
        imprime_deque(deque);
        putchar('\n');
    }

    destroi_deque(deque);

    return EXIT_SUCCESS;
}
