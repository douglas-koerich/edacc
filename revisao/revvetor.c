#include <stdlib.h>
#include <stdio.h>

void imprime_vetor(int [*], size_t);
void embaralha_vetor(int [*], size_t);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-elementos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num = atoi(argv[1]);
    if (num <= 0) {
        puts("Numero de elementos invalido");
        return EXIT_FAILURE;
    }
    int vetor[num];
    
    int i;
    for (i=0; i<num; ++i) {
        printf("Digite v[%d]: ", i);
        scanf("%d", &vetor[i]);
    }
    printf("Vetor original: ");
    imprime_vetor(vetor, num);
    putchar('\n');

    embaralha_vetor(vetor, num);

    printf("Vetor apos a mudanca: ");
    imprime_vetor(vetor, num);
    putchar('\n');

    return EXIT_SUCCESS;
}

void imprime_vetor(int v[], size_t n) {
    int i;
    for (i=0; i<n; ++i) {
        printf("%d ", v[i]);
    }
}

void embaralha_vetor(int v[], size_t n) {
    int aux[n], a, i;
    for (a=0, i=n/2+n%2; i<n; ++i, ++a) {
        aux[a] = v[i];
    }
    for (a=n-1, i=0; i<n/2+n%2; ++i, --a) {
        aux[a] = v[i];
    }
    for (i=0; i<n; ++i) {
        v[i] = aux[i];
    }
}

