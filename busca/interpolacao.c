#include "busca.h"

int busca(R vetor[], int inf, int sup, unsigned chave) {
    if (inf > sup) {
        return INVALIDO;
    }
    float dist_total_chaves = vetor[sup].chave - vetor[inf].chave,
          dist_chave_busca = chave - vetor[inf].chave;
    float proporcao = dist_total_chaves == 0? 0.0:
                      dist_chave_busca / dist_total_chaves;
    float dist_total_indices = sup - inf,
          dist_indice_chave = proporcao * dist_total_indices;
    int inter = inf + dis_indice_chave;
    if (vetor[inter].chave == chave) {
        return inter;
    }
    if (chave < vetor[inter].chave) {
        return busca(vetor, inf, inter-1, chave);
    } else {
        return busca(vetor, inter+1, sup, chave);
    }
}

