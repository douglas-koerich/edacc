#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "registro.h"
#include "ordenacao.h"

void imprime_chaves(R [*], size_t);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero invalido de parametros");
        printf("Uso: %s <tamanho-inicial>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    FILE* arq = fopen("/tmp/result.txt", "w");
    if (arq == NULL) {
        perror("Erro ao criar o arquivo");
        return EXIT_FAILURE;
    }
    fputs("n;t\n", arq);

    size_t n, tamanho = atoi(argv[1]);
    int amostras;
    for (amostras = 1, n = tamanho; amostras <= 1; ++amostras, n *= 2) {
        R* vetor = malloc(sizeof(R) * n);
        int i;
        for (i=0; i<n; ++i) {
            if (amostras == 1) {
                vetor[i].chave = rand() % 1000 + 1;
            } else {
                // Gera o vetor no pior caso, i.e., chaves em sequencia invertida
                vetor[i].chave = n - i; // ordem decrescente das chaves
            }
            vetor[i].valor = rand();
        }
        if (n < 100) {
            printf("Antes da ordenacao: ");
            imprime_chaves(vetor, n);
        }
        clock_t antes = clock();
        ordena(vetor, n);
        clock_t depois = clock();
        
        fprintf(arq, "%zd;%d\n", n, depois-antes);

        if (n < 100) {
            printf("\nDepois da ordenacao: ");
            imprime_chaves(vetor, n);
            putchar('\n');
        }
        free(vetor);
    }
    fclose(arq);
    return EXIT_SUCCESS;
}

void imprime_chaves(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        printf("%u ", v[i].chave);
    }
}
