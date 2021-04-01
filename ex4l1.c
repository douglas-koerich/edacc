#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

bool remover(Pilha*, int); // retira o elemento indicado por parametro

int main(void) {
    srand(2021);

    // Cria pilha para teste
    Pilha* S = create();

    // Preenche a pilha S1 com alguns numeros aleatorios
    int i;
    for (i = 1; i <= 5; ++i) {
        push(S, rand() % 100);
    }

    // Imprime o conteudo da pilha para conferencia
    puts("Pilha S");
    print(S);

    // Usuario seleciona o valor a ser removido
    int num;
    printf("\nDigite um numero em hexa para ser removido da pilha: ");
    scanf("%x", &num);

    if (remover(S, num)) {
        puts("\nO numero foi removido!");
    } else {
        puts("\nO numero nao estah na pilha!");
    }

    // Imprime o conteudo da pilha novamente
    puts("\nPilha S");
    print(S);

    // Finaliza destruindo a pilha criada
    destroy(S);

    return EXIT_SUCCESS;
}

bool remover(Pilha* p, int x) {
    Pilha* apoio = create();
    bool achou = false;

    while (!underflow(p)) {
        int valor = pop(p);
        if (valor != x) {
            push(apoio, valor);
        } else {
            achou = true;
        }
    }

    while (!underflow(apoio)) {
        push(p, pop(apoio));
    }

    destroy(apoio);

    return achou;
}