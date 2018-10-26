#include "ordenacao.h"

void bolha(Registro vetor[], size_t tamanho) {
    int passagem;
    // Passagens no vetor para garantir que, no pior caso, todas as
    // chaves fiquem em suas posicoes finais
    for (passagem = 1; passagem <= tamanho-1; ++passagem) {
        int posicao;
        for (posicao = tamanho-1; posicao > 0; --posicao) {
            // Chave da posicao atual estah fora de ordem em relacao
            // a chave da posicao anterior (numa ordem crescente)?
            if (vetor[posicao].chave < vetor[posicao-1].chave) {
                // Troca os registros de posicao (contiguidade fisica)
                troca_registros(vetor + posicao, vetor + posicao - 1);
            }
        }
    }
}

void selecao(Registro vetor[], size_t tamanho) {
    int posicao = 0;
    while (posicao < tamanho-1) {
        // Busca a frente da posicao atual uma chave que seja menor do
        // que aquela armazenada aqui
        int pos, pos_menor = posicao; // comeca assumindo que a menor estah aqui
        for (pos = posicao+1; pos < tamanho; ++pos) {
            if (vetor[pos].chave < vetor[pos_menor].chave) {
                pos_menor = pos; // atualiza a posicao da menor chave
            }
        }
        troca_registros(vetor + posicao, vetor + pos_menor);
        ++posicao; // uma vez selecionado o menor para essa posicao, repete
                   // o processo para a posicao seguinte, ateh o fim do vetor
    }
}

void insercao(Registro vetor[], size_t tamanho) {
    int posicao = 1; // primeira posicao que pode ser comparada com o segmento
                     // anterior ("para tras") do vetor
    while (posicao < tamanho) {
        int pos_anterior = posicao - 1;
        Registro bkp = vetor[posicao]; // salva o registro da posicao inicial,
                                       // pois essa posicao pode ser sobrescrita
                                       // com o que vier da anterior
        while (pos_anterior >= 0 && vetor[pos_anterior].chave > bkp.chave) {
            vetor[pos_anterior+1] = vetor[pos_anterior]; // "empurra" o registro
                                                         // com maior chave pra frente
            --pos_anterior;
        }
        // Duas condicoes podem ter terminado o laco acima:
        // 1) pos_anterior = -1 (todas as posicoes comparadas tinham chaves maiores!)
        // 2) Chegou-se numa pos_anterior com chave menor ou igual a que eu tinha
        vetor[pos_anterior+1] = bkp; // insere o backup na posicao correta
        ++posicao;
    }
}

