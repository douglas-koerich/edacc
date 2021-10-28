#include <stdlib.h>
#include <stdio.h>

void ordena(int*, size_t);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-elementos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    size_t num_elementos = atoi(argv[1]);
    int* vetor = malloc(num_elementos * sizeof(int));

    srand(20211028);
    int i;
    puts(">>> ANTES DA ORDENACAO:");
    for (i = 0; i < num_elementos; ++i) {
        vetor[i] = rand() % 100 + 1;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    puts(">>> DURANTE A ORDENACAO:");
    ordena(vetor, num_elementos);

    puts("<<< DEPOIS DA ORDENACAO:");
    for (i = 0; i < num_elementos; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    free(vetor);

    return EXIT_SUCCESS;
}
