/* PROBLEMA: escrever uma versao recursiva em C de uma funcao que recebe um
   vetor de numeros inteiros como parametro e devolve o maior valor nesse vetor
*/

#include <stdlib.h>
#include <stdio.h>

#define TAM_VETOR 5

int maior(const int*, size_t);

int main(void) {
    srand(1224);

    int vetor[TAM_VETOR], i;
    for (i = 0; i < TAM_VETOR; ++i) {
        int num = rand() % 1000;
        printf("%d ", num);
        vetor[i] = num;
    }

    int x = maior(vetor, TAM_VETOR);

    printf("\n%d\n", x);

    return EXIT_SUCCESS;
}

/*
// Versao iterativa (usual)
int maior(const int* v, size_t n) {
    int i, m = v[0];
    for (i = 1; i < n; ++i) {
        if (v[i] > m) {
            m = v[i];
        }
    }
    return m;
}
*/

// Versao recursiva
int maior(const int* v, size_t n) {
    if (n == 1) {       // condicao terminal
        return v[0];    // solucao trivial
    } else {
        int val1 = v[0];    // fase ativa da recursividade
        int val2 = maior(v + 1, n - 1); // chamada recursiva
        if (val1 > val2) {
            return val1;
        } else {
            return val2;
        }
    }
}

/*
v
                                            v
+---+---+---+---+---+---+---+---+---+---+---+---+
| 5 | 2 | 1 | 4 | 9 | 5 | 8 | 0 | 3 | 6 | 2 | 7 |
+---+---+---+---+---+---+---+---+---+---+---+---+
                                            /-1-/
/---------------------- n ----------------------/
*/

int maior2(const int* v, int i, int s) {
    if (i == s) {       // condicao terminal
        return v[i];    // solucao trivial
    } else { // fase ativa da recursividade
        int m = (i + s) / 2; // calcula indice no meio entre i e s
        int maior_i = maior2(v, i, m); // 1a. chamada recursiva
        int maior_s = maior2(v, m+1, s); // 2a. chamada recursiva
        if (maior_i > maior_s) {
            return maior_i;
        } else {
            return maior_s;
        }
    }
}