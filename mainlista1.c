#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerclista1.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // As funcoes terminadas com _p sao do TAD pilha,
    // para nao serem confundidas com as "homonimas"
    // dos outros TADs (fila e deque)
    PilhaInt* pilha = cria_p();
    while (!overflow_p(pilha)) {
        push(pilha, rand() % 10);
    }
    printf("Pilha inicial: ");
    print_p(pilha);
    putchar('\n');

    // As funcoes terminadas com _f sao do TAD fila
    FilaInt* fila = cria_f();
    while (!overflow_f(fila)) {
        enqueue_f(fila, rand() % 100);
    }
    printf("Fila inicial: ");
    print_f(fila);
    putchar('\n');
    
    // Apenas pra testar, vamos remover 2 elementos de cada estrutura
    pop(pilha); pop(pilha); // descarta simplesmente, sem salvar
    printf("\nPilha apos 2 remocoes (do topo!): ");
    print_p(pilha);
    putchar('\n');

    dequeue_f(fila); dequeue_f(fila);
    printf("Fila apos 2 remocoes (do inicio!): ");
    print_f(fila);
    putchar('\n');

    // Vamos ao que interessa, a execucao das funcoes
    // correspondentes aos exercicios.
    // Primeiro, o exercicio 4:
    int numero;
    printf("\nDigite um numero para remover da pilha: ");
    scanf("%d", &numero);
    if (exerc4lista1(pilha, numero) == true) {
        printf("Numero %d removido da pilha!\n", numero);
        printf("Pilha apos remocao(oes) de %d: ", numero);
        print_p(pilha);
        putchar('\n');
    } else {
        printf("Numero %d NAO foi encontrado na pilha!\n", numero);
    }

    // Agora, o exercicio 9:
    printf("\nDigite um numero maior do que aqueles que serao removidos da fila: ");
    scanf("%d", &numero);
    exerc9lista1(fila, numero);
    printf("Fila apos remocao(oes): ");
    print_f(fila);
    putchar('\n');

    destroi_p(pilha);
    destroi_f(fila);

    return EXIT_SUCCESS;
}

