#include <stdlib.h>
#include <stdio.h>
#include "generico2.h"
#include "deque.h"

void imprime_num(void*);
int compara_num(void*, void*);
Deque* intercala(Deque*, Deque*);

int main(int argc, char* argv[]) {
    int conjunto_1[] = { 1, 3, 5, 7, 9, -1 },
        conjunto_2[] = { 0, 2, 4, 6, 8, 10, 12, 14, -1 };

    Deque* deque_1 = cria();
    int i = 0;
    while (conjunto_1[i] >= 0) {
        generico g = {
            .coisa = &conjunto_1[i],
            .imprime = &imprime_num,
            .compara = &compara_num
        };
        enqueue(deque_1, FIM, &g);
        ++i;
    }
    Deque* deque_2 = cria();
    i = 0;
    while (conjunto_2[i] >= 0) {
        generico g = {
            .coisa = &conjunto_2[i],
            .imprime = &imprime_num,
            .compara = &compara_num
        };
        enqueue(deque_2, FIM, &g);
        ++i;
    }

    printf("Deque 1: ");
    imprime(deque_1);
    putchar('\n');
    printf("Deque 2: ");
    imprime(deque_2);
    putchar('\n');

    Deque* deque_3 = intercala(deque_1, deque_2);

    printf("\nDeque 3: ");
    imprime(deque_3);
    putchar('\n');

    printf("\nDeque 1: ");
    imprime(deque_1);
    putchar('\n');
    printf("Deque 2: ");
    imprime(deque_2);
    putchar('\n');

    destroi(deque_1);
    destroi(deque_2);
    destroi(deque_3);

    return EXIT_SUCCESS;
}

void imprime_num(void* n) {
    printf("%d", *((int*) n));
}

int compara_num(void* pi1, void* pi2) { // a-la strcmp()
    int* pint1 = pi1;
    int* pint2 = pi2;
    if (*pint1 == *pint2) {
        return 0;
    } else if (*pint1 > *pint2) {
        return 1;
    } else {
        return -1;
    }
}

Deque* intercala(Deque* d1, Deque* d2) {
    Deque* d = cria();
    Deque* d1_aux = cria();
    Deque* d2_aux = cria();
    generico* g;
    // Enquanto ambos as deques tem algum elemento armazenado...
    while (!underflow(d1) && !underflow(d2)) {
        // Eh necessario remover de ambos pra comparar
        generico* g1 = dequeue(d1, INICIO);
        generico* g2 = dequeue(d2, INICIO);
        if (g1->compara(g1->coisa, g2->coisa) < 0) {
            // O elemento de d1 eh menor, vai para o novo deque
            enqueue(d, FIM, g1);
            enqueue(d1_aux, FIM, g1);

            // Como o deque permite a insercao em ambas as extremidades, vamos
            // restituir o inicio de d2 com o elemento que foi removido para a
            // comparacao (g2)
            enqueue(d2, INICIO, g2);
        } else {
            enqueue(d, FIM, g2);
            enqueue(d2_aux, FIM, g2);
            enqueue(d1, INICIO, g1);
        }
        free(g1);
        free(g2);
    }
    // Para o caso de ter-se concluido o loop anterior pelo esvaziamento de d2
    while (!underflow(d1)) {
        g = dequeue(d1, INICIO);
        enqueue(d, FIM, g);
        enqueue(d1_aux, FIM, g);
        free(g);
    }
    // Para o caso de ter-se concluido o loop anterior pelo esvaziamento de d1
    while (!underflow(d2)) {
        g = dequeue(d2, INICIO);
        enqueue(d, FIM, g);
        enqueue(d2_aux, FIM, g);
        free(g);
    }
    // Restaura o conteudo dos deques originais
    while (!underflow(d1_aux)) {
        g = dequeue(d1_aux, INICIO);
        enqueue(d1, FIM, g);
        free(g);
    }
    while (!underflow(d2_aux)) {
        g = dequeue(d2_aux, INICIO);
        enqueue(d2, FIM, g);
        free(g);
    }
    destroi(d1_aux);
    destroi(d2_aux);
    return d;
}

