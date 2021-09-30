#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

/* Implemente um algoritmo que encontre o maior e o menor valor armazenados em
uma lista de numeros inteiros */

// Prototipo da funcao
void minmax(const int* lista, size_t tamanho, int* menor, int* maior);

int main(void) {
    srand((unsigned) time(NULL));

    const size_t TAMANHO = 6;
    int vetor[TAMANHO], i;

    for (i = 0; i < TAMANHO; ++i) {
        vetor[i] = rand() % 99 + 1;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int m, M;
    minmax(vetor, TAMANHO, &m, &M);
    printf("O menor valor eh %d e o maior eh %d\n", m, M);

    return EXIT_SUCCESS;
}

/*
// Versao iterativa ("convencional")
void minmax(const int* lista, size_t tamanho, int* menor, int* maior) {
    if (lista == NULL) {
        *menor = INT_MIN, *maior = INT_MAX;
        return;
    }
    *menor = *maior = lista[0];
    int i;
    for (i = 1; i < tamanho; ++i) {
        if (lista[i] < *menor) {
            *menor = lista[i];
        }
        if (lista[i] > *maior) {
            *maior = lista[i];
        }
    }
}
*/

/* Versao recursiva #1 (linear)
void minmax(const int* lista, size_t tamanho, int* menor, int* maior) {
    if (tamanho == 1) {
        *menor = *maior = lista[0];
        return; // aqui nao ha uma chamada para outra 'minmax()'
    } else {
        minmax(&lista[1], tamanho - 1, menor, maior); // chama o algoritmo
                                                      // RECURSIVAMENTE para
                                                      // examinar o restante

        // Ao voltar da chamada recursiva, pode-se comparar lista[0] com o que /// essa chamada descobriu como menor e maior valores 
        if (lista[0] < *menor) {
            *menor = lista[0];
        }
        if (lista[0] > *maior) {
            *maior = lista[0];
        }
    }
}
*/

// Versao recursiva #2 (multipla)
void minmax_(const int* lista, int inicio, int fim, int* menor, int* maior) {
    // Condicao terminal (base de recursao)
    if (fim < inicio) {
        return;
    }
    // Fase ativa (passo de recursao)
    int meio = (inicio + fim) / 2; // indice do meio do segmento
                                   // entre inicio e fim
    minmax_(lista, inicio, meio - 1, menor, maior);
    minmax_(lista, meio+1, fim, menor, maior);

    // Ao voltar das chamadas recursivas, pode-se comparar lista[meio] com o
    // que essas chamadas descobriram como menor e maior valores 
    if (lista[meio] < *menor) {
        *menor = lista[meio];
    }
    if (lista[meio] > *maior) {
        *maior = lista[meio];
    }
}

void minmax(const int* lista, size_t tamanho, int* menor, int* maior) {
    *menor = INT_MAX, *maior = INT_MIN; // para estabelecer uma
                                        // referencia inicial
    minmax_(lista, 0, tamanho - 1, menor, maior);
}