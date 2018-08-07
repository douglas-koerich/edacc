#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAMANHO 16

void bubblesort(int [*], size_t);
void coqueteleira(int [*], size_t);

int main(void) {
    srand(time(NULL));
    int* vetor = malloc(sizeof(int) * TAMANHO);
    int i;
    printf("Vetor original: ");
    for (i=0; i<TAMANHO; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    bubblesort(vetor, TAMANHO);
    printf("Vetor ordenado por bolha: ");
    for (i=0; i<TAMANHO; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    printf("Vetor original: ");
    for (i=0; i<TAMANHO; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    coqueteleira(vetor, TAMANHO);
    printf("Vetor ordenado por coqueteleira: ");
    for (i=0; i<TAMANHO; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    free(vetor);
    return EXIT_SUCCESS;
}

#define TROCA(a, b) \
    int aux = a; /* 2 */ \
    a = b;       /* 2 */ \
    b = aux;     /* 2 */

void bubblesort(int vetor[], size_t n) {
    int i, j;
    for (i=1; i<=n; ++i) {
        for (j=n-1; j>0; --j) {
            if (vetor[j] < vetor[j-1]) {
                TROCA(vetor[j], vetor[j-1]);
            }
        }
    }
}

/* Versao de bubblesort com lista encadeada
void bubblesort(ListaInt* l) {
    if (underflow(l)) {
        return;
    }
    int n = 1, i = 1;
    do {
        NoInt* x = l->cabeca;
        while (x->proximo != NULL) {
            if (i == 1) { // soh na primeira passagem...
                ++n;      // ... contabiliza o numero de nohs
            }
            if (x->valor > x->proximo->valor) {
                TROCA(x->valor, x->proximo->valor);
            }
            x = x->proximo;
        }
        ++i;
    } while (i <= n);
}
*/

void coqueteleira(int vetor[], size_t n) {
    int i, j;
    for (i=1; i<=n; ++i) {
        if (i % 2 == 0) {
            // Sobe o menor como no bolha original
            for (j=n-1; j>0; --j) {
                if (vetor[j] < vetor[j-1]) {
                    TROCA(vetor[j], vetor[j-1]);
                }
            }
        } else {
            // Desce o maior
            for (j=0; j<n-1; ++j) {
                if (vetor[j] > vetor[j+1]) {
                    TROCA(vetor[j], vetor[j+1]);
                }
            }
        }
    }
}

