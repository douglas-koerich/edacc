#include <stdlib.h>

size_t maiores2(int* vetor, int ind_inf, int ind_sup) { // indices inferior e superior
    if (ind_inf == ind_sup) {
        size_t contador = (vetor[ind_inf] > referencia)? 1: 0;
        return contador;
    }
    int ind_meio = (ind_inf + ind_sup) / 2; // posicao intermediaria do segmento
    size_t maiores_metade_inferior = maiores2(vetor, ind_inf, ind_meio);
    size_t maiores_metade_superior = maiores2(vetor, ind_meio+1, ind_sup);
    return maiores_metade_inferior + maiores_metade_superior;
}

