#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void bolha(int [*], size_t);
void coqueteleira(int [*], size_t);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand((unsigned) time(NULL));
    size_t tamanho = atoi(argv[1]);
    int* vetor = (int*) malloc(sizeof(int)*tamanho);
    int* copia = (int*) malloc(sizeof(int)*tamanho);
    int i;
    for (i=0; i<tamanho; ++i) {
        vetor[i] = rand() % 1000;
        copia[i] = vetor[i];
    }
    printf("Antes: ");
    for (i=0; i<tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    bolha(vetor, tamanho);
    coqueteleira(copia, tamanho);
    printf("Depois - bolha: ");
    for (i=0; i<tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    printf("Depois - coqueteleira: ");
    for (i=0; i<tamanho; ++i) {
        printf("%d ", copia[i]);
    }
    putchar('\n');
    free(vetor);
    free(copia);
    return EXIT_SUCCESS;
}

void bolha(int v[], size_t n) {
    int j;
    for (j=1; j<=n; ++j) {
        int i = n-1;
        while (i > 0) {
            if (v[i] < v[i-1]) {
                int aux = v[i];
                v[i] = v[i-1];
                v[i-1] = aux;
            }
            --i;
        }
    }
}

void coqueteleira(int v[], size_t n) {
    int j=1;
    while (j<=n) {
        if (j % 2) {    // passagem impar?
            // "leva a bolha para a superficie" (o menor valor para o inicio)
            int i = n-1;
            while (i > 0) {
                if (v[i] < v[i-1]) {
                    int aux = v[i];
                    v[i] = v[i-1];
                    v[i-1] = aux;
                }
                --i;
            }
        }
        else {  // passagem par?
            // "leva a pedra para o fundo" (o maior valor vai para o fim)
            int i = 0;
            while (i < n-1) {
                if (v[i] > v[i+1]) {
                    int aux = v[i];
                    v[i] = v[i+1];
                    v[i+1] = aux;
                }
                ++i;
            }
        }
        ++j;
    }
}
