#include <stdlib.h>
#include <stdio.h>
#include <time.h>

long long soma_v(const int* v, size_t n) {
    //         (M) ---------------------------> 1
    long long s = 0;
    int i;
    //    (M)    (R)  (M+A) ------------------> 1 + (n+1) + 2n
    for (i = 0; i < n; ++i) {
    //    (M+A+D) ----------------------------> 3n
        s += v[i];
    }
    // (M) -----------------------------------> 1
    return s; // -----------------------------: =============
} // -----------------------------------------> T(n) = 6n + 4

long long soma_m(const int* m, size_t o) {
    //         (M) ---------------------------> 1
    long long s = 0;
    int l, c;
    //    (M)    (R)   (M+A) -----------------> 1 + (n+1) + 2n
    for (l = 0; l < o; ++l) {
        //    (M)    (R)   (M+A) -------------> n.[1 + (n+1) + 2n] = 3n² + 2n
        for (c = 0; c < o; ++c) {
        //  (M+A)   (D)(A)(D) ----------------> n.5n = 5n²
            s += *(m + l*o + c);
        }
    }
    // (M) -----------------------------------> 1
    return s; // -----------------------------: ===================
} // -----------------------------------------> T(n) = 8n² + 5n + 4

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <tamanho>\n", argv[0]);
    }
    int tamanho = atoi(argv[1]);
    // int* vetor = malloc(tamanho * sizeof(int)); /* vetor */
    int* matriz = malloc(tamanho * tamanho * sizeof(int)); // matriz quadrada

    srand((unsigned) time(NULL));
    /*
    int indice;
    for (indice = 0; indice < tamanho; ++indice) {
        vetor[indice] = rand();
        // printf("%d ", vetor[indice]);
    }
    */
    int linha, coluna;
    for (linha = 0; linha < tamanho; ++linha) {
        for (coluna = 0; coluna < tamanho; ++coluna) {
            // matriz[linha][coluna] = rand();
            *(matriz + linha*tamanho + coluna) = rand();
            //printf("%10d ", *(matriz + linha*tamanho + coluna));
        }
        //putchar('\n');
    }

    // printf("\nSoma: %lld\n", soma_v(vetor, tamanho));
    printf("\nSoma: %lld\n", soma_m(matriz, tamanho));

    free(matriz);

    return EXIT_SUCCESS;
}