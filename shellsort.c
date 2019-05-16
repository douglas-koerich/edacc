#include "ordenacao.h"

#define NUM_INCREMENTOS 100

void ordena(R vetor[], size_t n) {
    int i, k, incrementos[NUM_INCREMENTOS];
    // Preenche o vetor ateh que o ultimo k seja menor que n
    for (i = 0, k = 1; k < n; ++i, k = 3*k + 1) {
        incrementos[i] = k;
    }
    int t = i-1; // indice do ultimo incremento no vetor (k menor que n)
    for (--t; t >= 0; --t) { // comecando do anterior, ateh o primeiro incremento (1)...
        k = incrementos[t];
        int s;
        for (s = 0; s < k; ++s) {  // para todos os segmentos formados pelo
                                   // salto no vetor com distancia k...
            i = s;
            while (i < n) {
                int indice_menor = i, j;
                for (j = i+k; j < n; j+=k) { // todos os deslocamentos dentro do segmento
                                             // sao feitos com base no incremento da vez (k)
                    if (vetor[j].chave < vetor[indice_menor].chave) {
                        indice_menor = j;
                    }
                }
                TROCA(vetor+i, vetor+indice_menor);
                i += k;
            }
        }
    }
}

