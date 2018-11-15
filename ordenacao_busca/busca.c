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

int interpolacao(Registro vetor[], int indice_inf, int indice_sup, unsigned chave_x) {
    ++comparacoes;
    if (indice_inf > indice_sup) {
        return -1;
    }
    int indice_provavel;
    if (indice_inf == indice_sup || vetor[indice_inf].chave == vetor[indice_sup].chave) {
        indice_provavel = indice_inf;
    } else {
        /* Regra de 3:
         * A distancia, em indices, da posicao provavel da chave buscada para o inicio do
         * segmento estah para a distancia em valor entre a chave buscada e o valor do inicio
         * "assim como"
         * a distancia, em indices, entre o fim e o inicio do segmento estah para a distancia
         * em valor entre a chave do fim e a chave do inicio
         */
        unsigned dist_valor_inf_x = chave_x - vetor[indice_inf].chave;
        unsigned dist_valor_inf_sup = vetor[indice_sup].chave - vetor[indice_inf].chave;
        int dist_indice_inf_sup = indice_sup - indice_inf;
        indice_provavel = dist_valor_inf_x * dist_indice_inf_sup
                          / dist_valor_inf_sup
                          + indice_inf;
    }
    if (vetor[indice_provavel].chave == chave_x) {
        return indice_provavel;
    }
    if (vetor[indice_provavel].chave < chave_x) {
        return interpolacao(vetor, indice_provavel+1, indice_sup, chave_x);
    } else {
        return interpolacao(vetor, indice_inf, indice_provavel-1, chave_x);
    }
}

