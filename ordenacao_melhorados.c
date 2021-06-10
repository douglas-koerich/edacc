#include "ordenacao.h"

void shellsort(Registro* vetor, size_t n) {
    // Geracao da serie de incrementos
    int incrementos[16], i = 0, k = 1;
    while (k < n) {
        incrementos[i++] = k;
        k = 3 * k + 1; // serie de Shell
    }
    i -= 2; // Comeca pelo termo da serie duas posicoes atras daquela
            // que seria a posicao do termo maior que n
    while (i >= 0) { // Para cada incremento decrescente...
        k = incrementos[i];
        int s; // Para repeticao do algoritmo pelos k segmentos do vetor
        for (s = 0; s < k; ++s) {
            // Utiliza o algoritmo de insercao como mecanismo de ordenacao
            int i; // Este 'i' NAO tem nada a ver com o 'i' do laco while!
            for (i = s + k; i < n; i += k) { // salta no vetor pelo incremento k
                Registro copia;
                memcpy(&copia, &vetor[i], sizeof(Registro));
                int j = i - k; // idem: salta no vetor pelo incremento k
                while (j >= 0 && vetor[j].chave > copia.chave) {
                    // Ibidem: salta no vetor pelo incremento k
                    memcpy(&vetor[j+k], &vetor[j], sizeof(Registro));
                    j -= k; 
                }
                memcpy(&vetor[j+k], &copia, sizeof(Registro));
            }
        }
        --i;
    }
}

void radixsort(Registro* vetor, size_t n) {
    
}