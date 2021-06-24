#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ordenacao.h" 

int main(void) {
    FILE* arquivo = fopen("/tmp/ordenacao.csv", "w");
    if (arquivo == NULL) {
        perror("Nao foi possivel criar o arquivo de comparacao");
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Bubble;Mergesort\n", arquivo);
    size_t tamanho = 1024;
    while (tamanho <= 128 * 1024) {
        fprintf(arquivo, "%zd;", tamanho);
        printf("Ordenando %zd elementos: ", tamanho);

        Registro* vetor1 = malloc(tamanho * sizeof(Registro));
        Registro* vetor2 = malloc(tamanho * sizeof(Registro));
        int i, j;
        for (i = 0, j = tamanho-1; i < tamanho; ++i, --j) {
            Registro r = { j, ' ' }; // preenche o vetor com chaves na
                                     // sequencia inversa dos indices
            memcpy(vetor1+i, &r, sizeof(Registro));
            memcpy(vetor2+i, &r, sizeof(Registro));

            if (i < 5) {
                printf("%d ", j);
            }
        }
        putchar('\n');

        clock_t antes, depois;

        antes = clock();
        bubble(vetor1, tamanho);
        depois = clock();
        fprintf(arquivo, "%ld;", depois-antes);

        antes = clock();
        mergesort(vetor2, 0, tamanho-1);
        depois = clock();
        fprintf(arquivo, "%ld\n", depois-antes);

        free(vetor1);
        free(vetor2);

        tamanho *= 2;
    }
    fclose(arquivo);

    return EXIT_SUCCESS;
}