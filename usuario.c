#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

// Programa-exemplo de uso de uma pilha para demonstrar
// o funcionamento da mesma ao inverter uma sequencia de
// valores digitados no teclado

int main(void) {
    size_t num_elementos;
    printf("Quantos valores serao digitados? ");
    scanf("%zu", &num_elementos);

    int i, vetor[num_elementos];

    printf("Digite os numeros na sequencia original:\n");
    for (i = 0; i < num_elementos; ++i) {
        printf("Numero? ");
        scanf("%d", &vetor[i]);
    }

    // Usuario declara uma variavel do tipo "Pilha", que eh o
    // TAD disponivel para realizar a operacao de inversao
    Pilha* p = cria(num_elementos); // capacidade minima da pilha

    puts("Sequencia original:");
    for (i = 0; i < num_elementos; ++i) {
        printf("%d ", vetor[i]);
        push(p, vetor[i]); // insere na pilha 'p' o numero da vez
    }

    puts("\nSequencia invertida:");
    // Para obter a sequencia invertida basta tirar da pilha
    // um elemento por vez (e soh eh possivel assim mesmo) ateh
    // que ela fique vazia
    while (!underflow(p)) {
        int num = pop(p);
        printf("%d ", num);
    }

    // Deve-se destruir a pilha antes de terminar o programa
    destroi(p);

    return EXIT_SUCCESS;
}

