#include <stdlib.h>
#include <stdio.h>
#include "generico2.h"
#include "fila.h"

void imprime_num(void*);
int compara_num(void*, void*);
Fila* intercala(Fila*, Fila*);

int main(int argc, char* argv[]) {
    int conjunto_1[] = { 1, 3, 5, 7, 9, -1 },
        conjunto_2[] = { 0, 2, 4, 6, 8, 10, 12, 14, -1 };

    Fila* fila_1 = cria();
    int i = 0;
    while (conjunto_1[i] >= 0) {
        generico g = {
            .coisa = &conjunto_1[i],
            .imprime = &imprime_num,
            .compara = &compara_num
        };
        enqueue(fila_1, &g);
        ++i;
    }
    Fila* fila_2 = cria();
    i = 0;
    while (conjunto_2[i] >= 0) {
        generico g = {
            .coisa = &conjunto_2[i],
            .imprime = &imprime_num,
            .compara = &compara_num
        };
        enqueue(fila_2, &g);
        ++i;
    }

    printf("Fila 1: ");
    imprime(fila_1);
    putchar('\n');
    printf("Fila 2: ");
    imprime(fila_2);
    putchar('\n');

    Fila* fila_3 = intercala(fila_1, fila_2);

    printf("\nFila 3: ");
    imprime(fila_3);
    putchar('\n');

    printf("\nFila 1: ");
    imprime(fila_1);
    putchar('\n');
    printf("Fila 2: ");
    imprime(fila_2);
    putchar('\n');

    destroi(fila_1);
    destroi(fila_2);
    destroi(fila_3);

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

Fila* intercala(Fila* f1, Fila* f2) {
    Fila* f = cria();
    Fila* f1_aux = cria();
    Fila* f2_aux = cria();
    generico* g;
    // Enquanto ambas as filas tem algum elemento armazenado...
    while (!underflow(f1) && !underflow(f2)) {
        // Eh necessario remover de ambas pra comparar
        generico* g1 = dequeue(f1);
        generico* g2 = dequeue(f2);
        if (g1->compara(g1->coisa, g2->coisa) < 0) {
            // O elemento de f1 eh menor, vai para a nova fila
            enqueue(f, g1);
            enqueue(f1_aux, g1);

            // Temos um problema aqui: pra fazer a comparacao, removemos de f2,
            // mas nao o incluimos na nova fila; ele deveria "voltar" pro inicio
            // de f2, mas po-lo em f2 vai fazer com que ele fique no fim.
            // Entao, usamos uma fila auxiliar pra recompor f2 do jeito que estava
            Fila* temp = cria();
            enqueue(temp, g2);
            while (!underflow(f2)) {
                generico* g = dequeue(f2);
                enqueue(temp, g);
                free(g);
            }
            while (!underflow(temp)) {
                generico* g = dequeue(temp);
                enqueue(f2, g);
                free(g);
            }
            destroi(temp);
        } else {
            enqueue(f, g2);
            enqueue(f2_aux, g2);
            Fila* temp = cria();
            enqueue(temp, g1);
            while (!underflow(f1)) {
                generico* g = dequeue(f1);
                enqueue(temp, g);
                free(g);
            }
            while (!underflow(temp)) {
                generico* g = dequeue(temp);
                enqueue(f1, g);
                free(g);
            }
            destroi(temp);
        }
        free(g1);
        free(g2);
    }
    // Para o caso de ter-se concluido o loop anterior pelo esvaziamento de f2
    while (!underflow(f1)) {
        g = dequeue(f1);
        enqueue(f, g);
        enqueue(f1_aux, g);
        free(g);
    }
    // Para o caso de ter-se concluido o loop anterior pelo esvaziamento de f1
    while (!underflow(f2)) {
        g = dequeue(f2);
        enqueue(f, g);
        enqueue(f2_aux, g);
        free(g);
    }
    // Restaura o conteudo das filas originais
    while (!underflow(f1_aux)) {
        g = dequeue(f1_aux);
        enqueue(f1, g);
        free(g);
    }
    while (!underflow(f2_aux)) {
        g = dequeue(f2_aux);
        enqueue(f2, g);
        free(g);
    }
    destroi(f1_aux);
    destroi(f2_aux);
    return f;
}
