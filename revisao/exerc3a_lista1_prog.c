/* Vetor de estruturas:
 * Colete um conjunto de N pontos no plano cartesiano e
 * classifique-os como pertencentes ao primeiro, segundo,
 * terceiro ou quarto quadrantes.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "exerc3_lista1_prog.h"

double rand_lf(void);

int main(void) {
    srand((unsigned) time(NULL));

    printf("Digite o numero de pontos a serem \"coletados\": ");
    size_t num_pontos;
    scanf("%zd", &num_pontos);

    // Vetor de estruturas
    // struct ponto colecao[num_pontos]; (sem o typedef)
    Ponto colecao[num_pontos]; // uma declaracao de vetor como qualquer outra

    // "Coleta" (geracao randomica) de pontos
    int i;
    for (i = 0; i < num_pontos; ++i) {
        colecao[i].x = rand_lf();
        colecao[i].y = rand_lf();
    }

    // Classificacao dos pontos
    for (i = 0; i < num_pontos; ++i) {
        int quadrante;
        if (colecao[i].x >= 0) {
            if (colecao[i].y >= 0) {
                quadrante = 1;
            } else {
                quadrante = 4;
            }
        } else {
            if (colecao[i].y >= 0) {
                quadrante = 2;
            } else {
                quadrante = 3;
            }
        }
        printf("O ponto (%lf,%lf) estah no %do. quadrante.\n",
               colecao[i].x, colecao[i].y, quadrante);
    }
    return EXIT_SUCCESS;
}

double rand_lf(void) {
    static const int NUM_CASAS_DECIMAIS = 9;
    int parte_inteira = rand() % 100;
    int sinal = rand() % 2; // 0 se positivo, 1 se negativo
    int parte_fracionaria = rand();
    double valor;
    if (sinal == 1) { // numero negativo?
        valor = -parte_inteira;
    } else {
        valor = parte_inteira;
    }
    valor += parte_fracionaria / pow(10, NUM_CASAS_DECIMAIS);
    return valor;
}

