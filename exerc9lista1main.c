#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerc9lista1fila.h"

int main() {
    srand((unsigned) time(0));

    // Cria uma fila e insere uma sequencia na mesma
    struct Fila* f = f_cria(100);
    int i;
    for (i=0; i<10; ++i) {
        enqueue(f, rand() % 50);
    }
    // Confirma a sequencia original da fila
    printf("Fila original: ");
    f_imprime(f);

    // Remove os elementos menores
    f_limpa_menores(f, 25);

    // Confirma a sequencia filtrada da fila
    printf("Fila apos remocao: ");
    f_imprime(f);

    // Destroi a fila usada como exemplo
    f_destroi(f);

    return 0;
}

