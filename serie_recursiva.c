/*
Escreva uma funcao recursiva para adicionar os primeiros "n" termos da serie
1 + 1/2 - 1/3 + 1/4 - 1/5 + ...

Definicao recursiva:
S(n) = 1, se n = 1
       S(n-1) + ((-1)^n)/n, se n > 1
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h> // pow()

float soma_serie(int n) {
    if (n == 1) {
        return 1;
    } else {
        return soma_serie(n-1) + pow(-1, n)/n;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <n>, onde 'n' eh o numero de termos da serie\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    
    float s = soma_serie(n);

    printf("O somatorio da serie com %d termos eh %f\n", n, s);

    return EXIT_SUCCESS;
}