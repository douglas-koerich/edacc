#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void bolha(int*, size_t);
void selecao(int*, size_t);
void insercao(int*, size_t);

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
    // puts(">>> ANTES DA ORDENACAO:");
    for (i = 0; i < num_elementos; ++i) {
        vetor[i] = rand() % 100 + 1;
        // printf("%d ", vetor[i]);
    }
    // putchar('\n');

    // puts(">>> DURANTE A ORDENACAO:");
    clock_t t1 = clock();
    ordena(vetor, num_elementos);
    clock_t t2 = clock();
    clock_t delta_t = t2 - t1;
    printf("%ld\n", delta_t);

    // puts("<<< DEPOIS DA ORDENACAO:");
    for (i = 0; i < num_elementos; ++i) {
        // printf("%d ", vetor[i]);
    }
    // putchar('\n');

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
    fprintf(arquivo, "Tamanho;Bolha;Selecao;Insercao\n");
    while (expoente <= 15) {
        size_t tamanho = pow(2, expoente);
        int* vetor_b = malloc(tamanho * sizeof(int));
        int* vetor_s = malloc(tamanho * sizeof(int));
        int* vetor_i = malloc(tamanho * sizeof(int));
        int i, n;
        for (i = 0, n = tamanho; i < tamanho; ++i, --n) {
            vetor_b[i] = n; // preenche o vetor com numeros em ordem decrescente
            vetor_s[i] = n;
            vetor_i[i] = n;
        }
        printf("Ordenando vetores com %zd elementos...\n", tamanho);
        clock_t t1, t2;
        t1 = clock();
        bolha(vetor_b, tamanho);
        t2 = clock();
        clock_t delta_b = t2 - t1;
        t1 = clock();
        selecao(vetor_s, tamanho);
        t2 = clock();
        clock_t delta_s = t2 - t1;
        t1 = clock();
        insercao(vetor_i, tamanho);
        t2 = clock();
        clock_t delta_i = t2 - t1;
        fprintf(arquivo, "%zd;%ld;%ld;%ld\n",
                tamanho, delta_b, delta_s, delta_i);
        free(vetor_b);
        free(vetor_s);
        free(vetor_i);
        ++expoente;
    }
    fclose(arquivo);

    return EXIT_SUCCESS;
}
