#include <stdlib.h>
#include <stdio.h>

#include "elemento.h"
#include "fila.h"

int main(void) {
    srand(1500);

    Fila* exemplo = create();

    puts("Fila eh criada inicialmente vazia:");
    print(exemplo);

    int i;
    for (i = 1; i <= 10; ++i) {
        TipoElemento x = rand() % 1000 + 1;
        enqueue(exemplo, x);
    }

    puts("Fila apos o preenchimento inicial:");
    print(exemplo);

    puts("<< Testes com a fila >>");
    printf("Elemento no inicio da fila: %d\n", front(exemplo));
    printf("Elemento no fim da fila: %d\n", rear(exemplo));
    printf("Neste momento ha %zu elementos na fila\n", size(exemplo));

    int n;
    printf("Digite quantos elementos deseja remover: ");
    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        TipoElemento x = dequeue(exemplo);
        printf("Foi removido o elemento %d\n", x);
    }

    puts("Fila apos as remocoes:");
    print(exemplo);
    printf("(%zu elementos restantes)\n", size(exemplo));

    destroy(exemplo);

    return EXIT_SUCCESS;
}