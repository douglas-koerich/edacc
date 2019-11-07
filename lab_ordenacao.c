#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "registro.h"
#include "alg_ordenacao.h"

int main(void) {
    FILE* planilha = fopen("/tmp/ordenacao.txt", "wt");
    if (planilha == NULL) {
        perror("Nao foi possivel criar a planilha");
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Bolha;Selecao;Insercao;Shell;Radix;Merge;Quick\n", planilha);
    clock_t antes, depois;
    size_t tamanho = 128;
    while (tamanho < 512*1024) {
        fprintf(planilha, "%zu;", tamanho);
        Reg* vetor = malloc(tamanho * sizeof(Reg));
        Reg* copia = malloc(tamanho * sizeof(Reg));
        int i, n;
        for (i = 0, n = tamanho; i < tamanho; ++i, --n) {
            vetor[i].chave = copia[i].chave = n; // vetores ordenados decrescentes
        }
        if (tamanho < 64*1024) {
            printf("Ordenando %zu registros por bolha...\n", tamanho);
            antes = clock();
            bolha(vetor, tamanho);
            depois = clock();
            fprintf(planilha, "%d;", depois-antes);
            memcpy(vetor, copia, tamanho*sizeof(Reg)); // comparar com o original
        } else {
            fputs("-;", planilha);
        }
        if (tamanho < 256*1024) {
            printf("Ordenando %zu registros por selecao..\n", tamanho);
            antes = clock();
            selecao(vetor, tamanho);
            depois = clock();
            fprintf(planilha, "%d;", depois-antes);
            memcpy(vetor, copia, tamanho*sizeof(Reg));
            printf("Ordenando %zu registros por insercao..\n", tamanho);
            antes = clock();
            insercao(vetor, tamanho);
            depois = clock();
            fprintf(planilha, "%d;", depois-antes);
            memcpy(vetor, copia, tamanho*sizeof(Reg));
            printf("Ordenando %zu registros por shell...\n", tamanho);
            antes = clock();
            shellsort(vetor, tamanho);
            depois = clock();
            fprintf(planilha, "%d;", depois-antes);
            memcpy(vetor, copia, tamanho*sizeof(Reg));
        } else {
            fputs("-;-;-;", planilha);
        }
        printf("Ordenando %zu registros por raiz...\n", tamanho);
        antes = clock();
        radixsort(vetor, tamanho);
        depois = clock();
        fprintf(planilha, "%d;", depois-antes);
        memcpy(vetor, copia, tamanho*sizeof(Reg));
        printf("Ordenando %zu registros por intercalacao...\n", tamanho);
        antes = clock();
        mergesort(vetor, 0, tamanho-1);
        depois = clock();
        fprintf(planilha, "%d;", depois-antes);
        memcpy(vetor, copia, tamanho*sizeof(Reg));
        printf("Ordenando %zu registros por quick...\n", tamanho);
        antes = clock();
        quicksort(vetor, 0, tamanho-1);
        depois = clock();
        fprintf(planilha, "%d;\n", depois-antes);

        free(vetor);
        free(copia);
        tamanho *= 2;
    }
    fclose(planilha);
    return EXIT_SUCCESS;
}

