#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned conta_i(int*, size_t, int);   // versao iterativa (com laco para repeticao)
unsigned conta_r(int*, size_t, int);   // versao recursiva (cada chamada executa um passo)

int main(void) {
    size_t tamanho;
    printf("Digite o tamanho do vetor a ser preenchido: ");
    scanf("%zd", &tamanho);

    int vetor[tamanho];
    srand(time(NULL));
    int i;
    printf("Vetor gerado: ");
    for (i=0; i<tamanho; ++i) {
        vetor[i] = rand() % 10;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int numero;
    printf("Digite o numero a ser contado no vetor: ");
    scanf("%d", &numero);

    unsigned n = conta_i(vetor, tamanho, numero);
    printf("Foram encontradas %u ocorrencias usando a versao iterativa.\n", n);

    n = conta_r(vetor, tamanho, numero);
    printf("Foram encontradas %u ocorrencias usando a versao recursiva.\n", n);

    return EXIT_SUCCESS;
}

unsigned conta_i(int* v, size_t t, int x) {
    unsigned n = 0;
    int i;
    for (i=0; i<t; ++i) {
        if (*(v+i) == x) {
            ++n;
        }
    }
    return n;
}

unsigned conta_r(int* v, size_t t, int x) {
    unsigned n = 0;
    if (t > 0) {
        if (*v == x) {
            ++n;
        }
        n += conta_r(v+1, t-1, x);
    }
    return n;
}
