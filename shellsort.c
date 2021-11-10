#include <stdlib.h>
#include <stdio.h>

void shell(int* v, size_t n) {
    // Gera a serie de incrementos a ser utilizada
    const size_t NUM_INCREMENTOS = 32;
    int k = 0, h = 1, incrementos[NUM_INCREMENTOS];
    // Gera o maximo de incrementos OU ate ultrapassar o tamanho
    // do vetor (pahra no incremento h_(n-1))
    while(k < NUM_INCREMENTOS && h < n) {
        incrementos[k++] = h;
        h = 3 * h + 1; // formula original de Shell
    }
    // Volta para a posicao anterior no vetor para iniciar com o
    // primeiro incremento da serie a ser usado
    --k;

    // Para todos os incrementos em ordem decrescente
    // (anteriores no vetor 'incrementos')...
    while (k >= 0) {
        h = incrementos[k];
        // O incremento da vez corresponde ao numero de segmentos
        // que dividem o vetor (com "saltos")
        int segmento;
        for (segmento = 0; segmento < h; ++segmento) {
            /* AQUI SE ENXERTA UM DOS ALGORITMOS DE ORDENACAO QUE JA VIMOS
               NAS AULAS ANTERIORES, LEMBRANDO QUE SE EXECUTA CONSIDERANDO
               OS ELEMENTOS QUE FAZEM PARTE DO MESMO SEGMENTO (EM "SALTOS"
               DE 'h') */
            int i;
            for (i = segmento + h; i < n; i += h) { // atuacao do incremento
                int r = v[i];
                int j;
                for (j = i-h; j >= 0 && v[j] > r; j -= h) {
                    v[j+h] = v[j];
                }
                v[j+h] = r;
            }
        }
        --k; // vai para o incremento menor...
    }
}
