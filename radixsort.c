#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

// Utiliza uma fila como estrutura de apoio
#include "fila.h"

void radix(int* v, size_t n) {
    const size_t NUM_MAX_DIGITOS = (size_t) log10(INT_MAX) + 1;
    const size_t NUM_SIMBOLOS = 10;

    // Cria o numero de filas correspondente ao numero de simbolos
    // do "alfabeto" dos componentes da chave
    fila* fila_digito[NUM_SIMBOLOS];
    int d;
    for (d = 0; d < NUM_SIMBOLOS; ++d) {
        fila_digito[d] = create(10000);
    }

    // Inicia a posicao pelo algarismo menos significativo das chaves
    // 5678 = 5 x 10^3 + 6 x 10^2 + 7 x 10^1 + 8 x 10^0
    int posicao = 0; // expoente 0
    while (posicao < NUM_MAX_DIGITOS) {
        // Para todos as chaves armazenadas no vetor...
        int i, numero;
        for (i = 0; i < n; ++i) {
            numero = v[i];

            // (descobre qual eh o digito do numero na posicao da vez)
            numero /= (int) pow(10, posicao);
            int digito = numero % 10;

            // ... coloca na fila o valor de acordo com o digito na posicao
            insert(fila_digito[digito], v[i]);
        }
        for (d = i = 0; d < NUM_SIMBOLOS; ++d) {
            while (!underflow(fila_digito[d])) {
                numero = extract(fila_digito[d]);
                v[i++] = numero;
            }
        }
        // EXTRA: imprime o vetor para acompanhar o algoritmo
        printf("Posicao: %d\n", posicao);
        for (i = 0; i < n; ++i) {
            printf("%d ", v[i]);
        }
        putchar('\n');

        ++posicao;
    }

    // Nao deve sair do algoritmo sem liberar as filas da memoria!
    for (d = 0; d < NUM_SIMBOLOS; ++d) {
        destroy(fila_digito[d]);
    }
}