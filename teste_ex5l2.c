#include <stdlib.h>
#include <stdio.h>
#include "ex5l2.h"

int main(void) {
    srand(505);

    Lista* lst = create();

    int i;
    for (i = 1; i <= 10; ++i) {
        insert(lst, rand() % 100);
    }
    puts("Conteudo da lista");
    print(lst);
    putchar('\n');

    int x, y;
    printf("Digite o limite inferior: ");
    scanf("%d", &x);
    printf("Limite superior: ");
    scanf("%d", &y);

    delete_range(lst, x, y);

    puts("Apos a remocao do intervalo");
    print(lst);
    putchar('\n');

    destroy(lst);

    return EXIT_SUCCESS;
}