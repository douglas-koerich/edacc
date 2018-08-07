#include <stdio.h>
#include "exerc8lista1fila.h"

int main() {
    unsigned vet[] = { 1, 2, 3, 5, 8, 13, 21, 34, 0 };

    // Cria uma fila e insere uma sequencia na mesma
    struct Fila* f = f_cria(100);
    int i = 0;
    while (vet[i] > 0) {
        enqueue(f, vet[i]);
        ++i;
    }
    // Confirma a ordem original da fila
    printf("Fila original: ");
    f_imprime(f);

    // Inverte a sequencia da fila
    f_inverte(f);

    // Confirma a ordem invertida da fila
    printf("Fila invertida: ");
    f_imprime(f);

    // Destroi a fila usada como exemplo
    f_destroi(f);

    return 0;
}

