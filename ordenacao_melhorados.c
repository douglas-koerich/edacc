#include "ordenacao.h"
#include "fila_registros.h"

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
    // Cria as 10 filas correspondentes aos 10 simbolos (algarismos)
    // que compoem a chave numerica
    const size_t NUM_SIMBOLOS = 10;
    int i;
    Fila* filas[NUM_SIMBOLOS];
    for (i = 0; i < NUM_SIMBOLOS; ++i) {
        filas[i] = f_create();
    }
    // Como a chave do registro eh do tipo 'int', vamos considerar desde a
    // posicao correspondente ah unidade (10^0) ateh a posicao correspondente ah
    // unidade de bilhao (10^9)
    int expoente;
    for (expoente = 0; expoente <= 9; ++expoente) {
        // Percorre o vetor inspecionando o digito correspondente ao expoente
        // da vez
        for (i = 0; i < n; ++i) {
            int chave = vetor[i].chave;
            // Descarta os digitos ah direita do expoente em questao
            int e;
            for (e = 0; e < expoente; ++e) {
                chave /= 10;
            }
            int digito = chave % 10;
            f_enqueue(filas[digito], &vetor[i]);
        }
        int j;
        for (i = j = 0; i < NUM_SIMBOLOS; ++i) {
            while (!f_underflow(filas[i])) {
                Registro* r = f_dequeue(filas[i]);
                vetor[j++] = *r;
                free(r); // libera a memoria alocada pela operacao f_dequeue
            }
        }
    }
    for (i = 0; i < NUM_SIMBOLOS; ++i) {
        f_destroy(filas[i]);
    }
}