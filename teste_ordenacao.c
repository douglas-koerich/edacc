#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void bolha(int*, size_t);
void selecao(int*, size_t);
void insercao(int*, size_t);
void shell(int*, size_t);
void radix(int*, size_t);
void merge(int*, int, int);
void quick(int*, int, int);

/*
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
        vetor[i] = rand() % 1000 + 1;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    puts(">>> DURANTE A ORDENACAO:");
    clock_t t1 = clock();
    quick(vetor, 0, num_elementos-1);
    clock_t t2 = clock();
    clock_t delta_t = t2 - t1;
    // printf("%ld\n", delta_t);

    puts("<<< DEPOIS DA ORDENACAO:");
    for (i = 0; i < num_elementos; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    free(vetor);

    return EXIT_SUCCESS;
}
*/

int main(void) {
    FILE* arquivo = fopen("medicao.csv", "wt");
    if (arquivo == NULL) {
        perror("Nao foi possivel criar o arquivo");
        return EXIT_FAILURE;
    }
    int expoente = 10;
    fprintf(arquivo, "Tamanho;Bolha;Selecao;Insercao;Shell;Merge;Quick\n");
    while (expoente <= 24) {
        size_t tamanho = pow(2, expoente);
        int* vetor_b = malloc(tamanho * sizeof(int));
        int* vetor_s = malloc(tamanho * sizeof(int));
        int* vetor_i = malloc(tamanho * sizeof(int));
        int* vetor_h = malloc(tamanho * sizeof(int));
        int* vetor_m = malloc(tamanho * sizeof(int));
        int* vetor_q = malloc(tamanho * sizeof(int));
        int i, n;
        for (i = 0, n = tamanho; i < tamanho; ++i, --n) {
            vetor_b[i] = vetor_s[i] = vetor_i[i] = vetor_h[i] =
                vetor_m[i] = vetor_q[i] = n;
        }
        printf("Ordenando vetores com %zd elementos...\n", tamanho);
        clock_t t1, t2, delta_b = 0, delta_s = 0, delta_i = 0;
        if (expoente <= 16) {
            t1 = clock();
            bolha(vetor_b, tamanho);
            t2 = clock();
            delta_b = t2 - t1;
            t1 = clock();
            selecao(vetor_s, tamanho);
            t2 = clock();
            delta_s = t2 - t1;
            t1 = clock();
            insercao(vetor_i, tamanho);
            t2 = clock();
            delta_i = t2 - t1;
        }
        t1 = clock();
        shell(vetor_h, tamanho);
        t2 = clock();
        clock_t delta_h = t2 - t1;
        t1 = clock();
        merge(vetor_m, 0, tamanho-1);
        t2 = clock();
        clock_t delta_m = t2 - t1;
        t1 = clock();
        quick(vetor_q, 0, tamanho-1);
        t2 = clock();
        clock_t delta_q = t2 - t1;
        fprintf(arquivo, "%zd;%ld;%ld;%ld;%ld;%ld;%ld\n",
                tamanho, delta_b, delta_s, delta_i,
                delta_h, delta_m, delta_q);
        free(vetor_b);
        free(vetor_s);
        free(vetor_i);
        free(vetor_h);
        free(vetor_m);
        free(vetor_q);
        ++expoente;
    }
    fclose(arquivo);

    return EXIT_SUCCESS;
}