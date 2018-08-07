#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha_inteiros.h"

int main() {
    int sequencia[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, -1 };

    // Cria uma pilha para receber a sequencia de numeros
    PilhaInt* pilha = cria_pilha();

    int i = 0;
    printf("Empilhando: ");
    while (sequencia[i] > 0) {
        printf("%d ", sequencia[i]);
        if (overflow(pilha) == false) {
            push(pilha, sequencia[i]);
        }
        ++i;
    }
    putchar('\n');

    // Imprime a pilha para verificar o conteudo
    puts("Pilha:");
    imprime_pilha(pilha);

    // Recupera a sequencia invertida
    printf("Retirando da pilha: ");
    while (underflow(pilha) == false) {
        int num = pop(pilha);
        printf("%d ", num);
    }
    putchar('\n');

    // Nao esquece de destruir a estrutura de dados: pilha alocada na memoria
    destroi_pilha(pilha);

    return EXIT_SUCCESS;
}
