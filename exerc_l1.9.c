#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "deque.h"

// Funcoes requeridas pelo tipo generico
void imprime_letra(void*);
int compara_letra(void*, void*);

// Funcao que implementa o exercicio: repare que ela recebe o valor de
// referencia atraves do seu endereco em tipo void*
void retira_menores(Deque*, void*);

int main(int argc, char* argv[]) {
    char conjunto[] = { 'E', 'S', 'T', 'R', 'U', 'T', 'U', 'R', 'A', 'S',
                        'D', 'E', 'D', 'A', 'D', 'O', 'S', ' ' };

    Deque* deque = cria();

    int i = 0;
    while (isalpha(conjunto[i])) {
        generico g = {
            .coisa = &conjunto[i],
            .imprime = &imprime_letra,
            .compara = &compara_letra
        };
        enqueue(deque, FIM, &g);
        ++i;
    }
    puts("Deque ANTES da remocao:");
    imprime(deque);
    putchar('\n');

    printf("Digite um valor de referencia: ");
    char valor;
    scanf(" %c", &valor);
    valor = toupper(valor);

    retira_menores(deque, &valor);

    puts("Deque DEPOIS da remocao:");
    imprime(deque);
    putchar('\n');

    destroi(deque);

    return EXIT_SUCCESS;
}

void imprime_letra(void* pv) {
    char* pc = pv;
    putchar(*pc);
}

int compara_letra(void* pv1, void* pv2) {
    char* pc1 = pv1;
    char* pc2 = pv2;
    if (*pc1 > *pc2) {
        return 1;
    } else if (*pc1 < *pc2) {
        return -1;
    } else {
        return 0;
    }
}

void retira_menores(Deque* d, void* ref) {
    // Compare essa solucao com a do exercicio 4, e verah que sao
    // funcionalmente identicas, porque estamos usando os deques
    // (original e auxiliar) como se fossem duas "pilhas"! Confira...
    Deque* aux = cria();
    while (!underflow(d)) {
        generico* g = dequeue(d, INICIO);
        if (g->compara(g->coisa, ref) >= 0) {
            enqueue(aux, FIM, g);
        }
        free(g);
    }
    while (!underflow(aux)) {
        generico* g = dequeue(aux, FIM);
        enqueue(d, INICIO, g);
        free(g);
    }
    destroi(aux);
}

