#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

// Programa-exemplo de uso de uma fila para demonstrar
// o funcionamento da mesma para "lembrar" a ordem dos
// valores digitados no teclado

int main(void) {
    size_t num_elementos;
    printf("Quantos valores serao digitados? ");
    scanf("%zu", &num_elementos);

    // Usuario declara uma variavel do tipo "Fila", que eh o
    // TAD disponivel para armazenar a "cronologia" dos valores
    Fila* f = cria(num_elementos); // capacidade minima da fila

    printf("Digite os numeros:\n");
    int i, num;
    for (i = 0; i < num_elementos; ++i) {
        printf("Numero? ");
        scanf("%d", &num);
        insere(f, num);
    }

    // Remove uns 2 numeros pra ilustrar
    puts("Removendo 2 numeros...");
    retira(f);
    retira(f);

    puts("Sequencia de digitacao:");
    while (!underflow(f)) {
        num = retira(f);
        printf("%d ", num);
    }
    putchar('\n');

    // Deve-se destruir a fila antes de terminar o programa
    destroi(f);

    return EXIT_SUCCESS;
}

