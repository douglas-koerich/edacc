#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

extern int contador;
void quick(int*, int, int);
int sequencial(int*, size_t, int);
int binaria(int*, int, int, int);
int interpolacao(int*, int, int, int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-elementos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t num_elementos = atoi(argv[1]);
    int* vetor = malloc(num_elementos * sizeof(int));

    srand(20211028);
    int indice;
    for (indice = 0; indice < num_elementos; ++indice) {
        vetor[indice] = rand() % 10000 + 1;
    }
    quick(vetor, 0, num_elementos-1);
    if (num_elementos <= 30) {
        for (indice = 0; indice < num_elementos; ++indice) {
            printf("%d ", vetor[indice]);
        }
        putchar('\n');
    }
    contador = 0;
    sequencial(vetor, num_elementos, vetor[num_elementos-1]);
    printf("sequencial: %u comparacoes\n", contador);

    contador = 0;
    binaria(vetor, 0, num_elementos-1, vetor[num_elementos-1]);
    printf("binaria: %u comparacoes\n", contador);

    contador = 0;
    interpolacao(vetor, 0, num_elementos-1, vetor[num_elementos-1]);
    printf("binaria: %u comparacoes\n", contador);

    free(vetor);

    return EXIT_SUCCESS;
}