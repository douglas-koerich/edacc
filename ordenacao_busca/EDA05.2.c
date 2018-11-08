#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"

void bolha_melhorada(Registro vetor[], size_t tamanho) {
    int passagem;
    bool trocou;
    for (passagem = 1, trocou = true; passagem <= tamanho-1 && trocou == true; ++passagem) {
        int posicao;
        trocou = false;
        for (posicao = tamanho-1; posicao > 0; --posicao) {
            if (vetor[posicao].chave < vetor[posicao-1].chave) {
                troca_registros(vetor + posicao, vetor + posicao - 1);
                trocou = true;
            }
        }
    }
}

