#include "busca.h"

unsigned comparacoes;

int sequencial(Registro vetor[], size_t tamanho, unsigned chave_x) {
    int i;
    for (i=0; i<tamanho; ++i) {
        ++comparacoes;
        if (vetor[i].chave == chave_x) {
            return i;
        }
    }
    return -1; // chave_x nao encontrada em nenhum elemento
}

int binaria(Registro vetor[], int indice_inf, int indice_sup, unsigned chave_x) {
    ++comparacoes;
    if (indice_inf > indice_sup) { // o segmento onde poderia fazer a busca se tornou nulo
        return -1; // a chave nao foi encontrada em nenhum segmento anterior
    }
    int indice_meio = (indice_inf + indice_sup) / 2;
    if (vetor[indice_meio].chave == chave_x) {
        return indice_meio; // encontrei a chave aqui! :-)
    }
    if (vetor[indice_meio].chave < chave_x) {
        // Continua a busca (e retorna o resultado) na metade superior
        return binaria(vetor, indice_meio+1, indice_sup, chave_x);
    } else {
        // Continua a busca na metade inferior
        return binaria(vetor, indice_inf, indice_meio-1, chave_x);
    }
}

