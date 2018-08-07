#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUMEROS_SORTEADOS   6
#define MAX_NUMEROS_APOSTA  12
#define MAX_NUMERO          60

int main() {
    srand((unsigned) time(0));
    int sorteados[NUMEROS_SORTEADOS], i;
    for (i=0; i<NUMEROS_SORTEADOS; ++i) {
        sorteados[i] = rand() % MAX_NUMERO + 1;
    }
    int numeros;
    do {
        printf("Digite quantos numeros apostara: ");
        scanf("%d", &numeros);
    } while (numeros < NUMEROS_SORTEADOS || numeros > MAX_NUMEROS_APOSTA);

    //int aposta[numeros];
    int* aposta = (int*) malloc(numeros * sizeof(int)); // tamanho em bytes

    puts("Digite sua aposta:");
    for (i=0; i<numeros; ++i) {
        do {
            printf("%do. numero? ", i+1);
            // scanf("%d", &aposta[i]);
            scanf("%d", aposta+i);  // dah ao scanf o endereco relativo do vetor
        } while (aposta[i] < 1 || aposta[i] > MAX_NUMERO);
    }
    printf("Numeros sorteados: ");
    for (i=0; i<NUMEROS_SORTEADOS; ++i) {
        printf("%02d ", sorteados[i]);
    }
    putchar('\n');
    printf("Numeros apostados: ");
    for (i=0; i<numeros; ++i) {
        printf("%02d ", aposta[i]);
    }
    putchar('\n');

    free(aposta);   // se nao chamar, pode ficar com lixo na memoria

    return EXIT_SUCCESS;
}
