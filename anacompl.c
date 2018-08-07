/* Dados dois vetores de tamanho 'n', onde o primeiro nao contem valores
 * repetidos, elabore uma funcao que contabilize num terceiro vetor quantas
 * ocorrencias de cada valor do primeiro sao encontradas no segundo.
 *
 * Em seguida, determine a funcao de complexidade T(n) do algoritmo.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void repetidos(int v1[*], int v2[*], int rep[*], size_t n);
void imprime(int v[*], size_t n);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho> ou 0 para escala de Ns\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t n = atoi(argv[1]);
    if (n > 0) {
        int primeiro[n], segundo[n], repeticoes[n];

        srand(n);
        int i;
        for (i = 0; i < n; ++i) {
            primeiro[i] = i;
            segundo[i] = rand() % n;
        }

        repetidos(primeiro, segundo, repeticoes, n);

        puts("Primeiro:");
        imprime(primeiro, n); putchar('\n');
        puts("Segundo:");
        imprime(segundo, n); putchar('\n');
        puts("Repeticoes:");
        imprime(repeticoes, n); putchar('\n');
    } else {
        FILE* csv = fopen("/tmp/anacompl.csv", "wt");
        if (csv == NULL) {
            perror("Erro ao criar arquivo");
            return EXIT_FAILURE;
        }
        fputs("n;T(n)\n", csv);
        for (n = 1024; n <= 262144; n *= 2) {
            printf("Para vetores com %zd elementos...\n", n);
            int* primeiro = malloc(n*sizeof(int));
            int* segundo = malloc(n*sizeof(int));
            int* repeticoes = malloc(n*sizeof(int));

            srand(n);
            int i;
            for (i=0; i<n; ++i) {
                primeiro[i] = i;
                segundo[i] = rand() % n;
            }

            clock_t antes = clock();
            repetidos(primeiro, segundo, repeticoes, n);
            clock_t depois = clock();
            fprintf(csv, "%zd;%ld\n", n, depois-antes);

            free(repeticoes);
            free(segundo);
            free(primeiro);
        }
        fclose(csv);
    }
    return EXIT_SUCCESS;
}

void imprime(int v[], size_t n) {
    int i;
    for (i=0; i<n; ++i) {
        printf("%d ", v[i]);
    }
}

void repetidos(int v1[], int v2[], int rep[], size_t n) {
    int i1;
    for (i1=0; i1<n; ++i1) {
        rep[i1] = 0;
        int i2;
        for (i2=0; i2<n; ++i2) {
            if (v2[i2] == v1[i1]) {
                ++rep[i1];
            }
        }
    }
}

/* ANALISE DA COMPLEXIDADE
void repetidos(int v1[], int v2[], int rep[], size_t n) { ---> 0 (nao executa)
    int i1;         -----------------------------------------> 0 (idem)
    for (i1 = 0;    -----------------------------------------> 2 (le 0, escr i1)
         i1 < n;    -----------------------------------------> 3.(n+1) = 3n+3
         ++i1) {    -------------------------- i1 =i1 + 1 ---> 4n
        rep[i1] = 0;-----------------------------------------> 5n
        int i2;     -----------------------------------------> 0 (soh declara)
        for (i2=0;  -----------------------------------------> 2n
             i2<n;  -----------------------------------------> 3.(n+1).n = 3n²+3n
             ++i2) {-----------------------------------------> 4n²
            if (v2[i2] == v1[i1]) {--------------------------> (4+1+4)n² = 9n²
                ++rep[i1]; -------- rep[i1] = rep[i1] + 1 ---> 10n²
            }       =============================================================
        }                                               T(n) = 26n² + 17n + 5
    }
}
*/
