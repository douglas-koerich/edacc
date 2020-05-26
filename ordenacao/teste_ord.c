#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "registro.h"

void bolha(R [*], size_t);
void selecao(R [*], size_t);
void insercao(R [*], size_t);
void shellsort(R [*], size_t);
void radixsort(R [*], size_t);
void mergesort(R [*], int, int);
void quicksort(R [*], int, int);

int main(int argc, char* argv[]) {
    FILE* arq = fopen("/tmp/result.txt", "w");
    if (arq == NULL) {
        perror("Erro ao criar o arquivo");
        return EXIT_FAILURE;
    }
    fputs("n;bolha;selecao;insercao;shellsort;radixsort;mergesort;quicksort\n", arq);

    size_t n = 1024;
    while (n < 1024 * 1024) {
        printf("Ordenando %zu registros... ", n);
        fflush(stdout);

        fprintf(arq, "%zu;", n);
        R* vetor = malloc(sizeof(R) * n);
        int i;
        unsigned j;
        for (i = 0, j = n; i < n; ++i, --j) {
            vetor[i].chave = j;
        }
        R* copia = malloc(sizeof(R) * n);

        clock_t antes, depois;
        if (n < 128 * 1024) {
            memcpy(copia, vetor, sizeof(R) * n);
            putchar('b'); fflush(stdout);
            antes = clock();
            bolha(copia, n);
            depois = clock();
            fprintf(arq, "%d;", depois-antes);

            memcpy(copia, vetor, sizeof(R) * n);
            putchar('s'); fflush(stdout);
            antes = clock();
            selecao(copia, n);
            depois = clock();
            fprintf(arq, "%d;", depois-antes);

            memcpy(copia, vetor, sizeof(R) * n);
            putchar('i'); fflush(stdout);
            antes = clock();
            insercao(copia, n);
            depois = clock();
            fprintf(arq, "%d;", depois-antes);

            memcpy(copia, vetor, sizeof(R) * n);
            putchar('h'); fflush(stdout);
            antes = clock();
            shellsort(copia, n);
            depois = clock();
            fprintf(arq, "%d;", depois-antes);
        } else {
            fprintf(arq, "-;-;-;-;");
        }
        memcpy(copia, vetor, sizeof(R) * n);
        putchar('r'); fflush(stdout);
        antes = clock();
        radixsort(copia, n);
        depois = clock();
        fprintf(arq, "%d;", depois-antes);

        memcpy(copia, vetor, sizeof(R) * n);
        putchar('m'); fflush(stdout);
        antes = clock();
        mergesort(copia, 0, n-1);
        depois = clock();
        fprintf(arq, "%d;", depois-antes);

        memcpy(copia, vetor, sizeof(R) * n);
        putchar('q'); fflush(stdout);
        antes = clock();
        quicksort(copia, 0, n-1);
        depois = clock();
        fprintf(arq, "%d\n", depois-antes);

        printf(" Feito!\n");

        free(copia);
        free(vetor);
        n *= 2;
    }
    fclose(arq);
    return EXIT_SUCCESS;
}

