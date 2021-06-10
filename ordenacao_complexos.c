#include "ordenacao.h"

void bubble(Registro* vetor, size_t n) {
    // Laco externo: varreduras
    int i;
    for (i = 1; i < n; ++i) {
        // Laco interno: comparacao entre posicoes
        int j;
        for (j = n-1; j >= i; --j) {
            if (vetor[j].chave < vetor[j-1].chave) {
                TROCA(vetor[j], vetor[j-1]);
            }
        }
    }
}

void selection(Registro* vetor, size_t n) {
    // Laco externo: numero de buscas pelo menor
    int i;
    for (i = 0; i < n-1; ++i) {
        int i_menor = i; // posicao do menor valor encontrado
        int j;
        // Laco interno: busca pelo menor a partir da posicao i
        for (j = i+1; j < n; ++j) {
            if (vetor[j].chave < vetor[i_menor].chave) {
                i_menor = j; // atualiza o indice correspondente ah
                             // posicao do menor valor
            }
        }
        TROCA(vetor[i], vetor[i_menor]);
    }
}

void insertion(Registro* vetor, size_t n) {
    // Laco externo: numero de valores para inserir ah esquerda
    // (na parte jah ordenada do vetor)
    int i;
    for (i = 1; i < n; ++i) {
        // Guarda em lugar seguro (nao sobrescrito) o registro que se
        // quer colocar na parte jah ordenada
        Registro copia;
        memcpy(&copia, &vetor[i], sizeof(Registro));

        // Laco interior: busca pela posicao correta desse valor
        // na parte jah ordenada
        int j = i - 1; // inicio (lado direito) da parte jah ordenada
        while (j >= 0 && vetor[j].chave > copia.chave) {
            memcpy(&vetor[j+1], &vetor[j], sizeof(Registro));
            --j;
        }
        // O laco acima termina se:
        // a) A chave em 'copia' eh a menor de todas, entao j = -1 nesse ponto
        // b) A chave em j eh menor do que a em 'copia', vai por copia em j+1
        memcpy(&vetor[j+1], &copia, sizeof(Registro));
    }
}
