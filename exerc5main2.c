#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerc5lista2.h"

int main() {
    srand((unsigned) time(0));

    struct Lista* l = cria();

    int i;
    for (i=1; i<=5; ++i) {
        float n = (rand() % 100000) / 100.0;
        inserirInicio(l, n);
        imprime(l);
    }
    printf("Digite o limite inferior: ");
    float min;
    scanf("%f", &min);
    printf("Digite o limite superior: ");
    float max;
    scanf("%f", &max);
    removerIntervalo(l, min, max);
    imprime(l);

    destroi(l);

    return 0;
}

