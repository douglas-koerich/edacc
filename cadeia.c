#include <string.h>
#include <limits.h>
#include "cadeia.h"

int forca_bruta(const char* texto, const char* padrao) {
    size_t n = strlen(texto), m = strlen(padrao);
    int i;

    // Percorre o texto caractere a caractere, postulando que o caractere
    // possa ser o inicio do padrao
    for (i=0; i<(n-m+1); ++i) { // ultimo caractere leva em consideracao o
                                // comprimento do padrao (m)
        int p=0, t=i;

        // Verifica coincidencias a partir deste caractere por toda a
        // extensao do comprimento do padrao
        while (p<m && padrao[p] == texto[t]) {
            ++p, ++t;
        }
        // Se todo o comprimento do padrao foi examinado, houve casamento
        if (p == m) {
            return i;
        }
    }
    return -1; // Apos varredura completa, padrao nao encontrado no texto
}

int shift_and(const char* texto, const char* padrao) {
    // Pre-processamento do padrao
    long long mascaras_padrao[CHAR_MAX+1] = { 0 };  // palavras com ateh 64 caracteres
    size_t m = strlen(padrao);
    int i;
    for (i=0; i<m; ++i) {
        // Seta o bit (1) correspondente a posicao do caractere no padrao
        // Exemplo: No padrao 'teste':
        // mascaras_padrao[t] = 10010
        // mascaras_padrao[e] = 01001
        // mascaras_padrao[s] = 00100
        // outras entradas mascaras_padrao[...] ficam nulas
        mascaras_padrao[padrao[i]] |= 1 << (m-i-1);
    }
    // Uso da mascara do padrao na varredura do texto
    long long mascara = 0;
    size_t n = strlen(texto);
    for (i=0; i<n; ++i) {
        mascara = (mascara >> 1 | 1 << (m-1)) & mascaras_padrao[texto[i]];
        if (mascara & 1) {
            return i-m+1;
        }
    }
    return -1;
}

int boyer_moore(const char* texto, const char* padrao) {
    // Pre-processamento do padrao
    size_t m = strlen(padrao);
    int i, deslocamentos[CHAR_MAX+1];

    // Todos os caracteres possiveis sao inicialmente considerados
    // "fora" (ausentes, alem do limite direito) do padrao
    for (i=0; i<=CHAR_MAX; ++i) {
        deslocamentos[i] = m+1;
    }
    // Calcula a menor distancia de cada caractere do padrao ao limite
    // direito (fim) do mesmo
    for (i=0; i<m; ++i) {
        deslocamentos[padrao[i]] = m-i;
    }
    // Pesquisa no texto
    i = m-1;
    size_t n = strlen(texto);
    while (i < n) {
        // Procura o padrao de tras para frente (direita para esquerda)
        int p=m-1, t=i;
        while (p >= 0 && padrao[p] == texto[t]) {
            --p, --t;
        }
        if (p < 0) {
            return t+1;
        }
        // Se nao encontrou nessa comparacao entre o trecho do texto e
        // o padrao, desloca com base no ultimo caractere "descasado"
        i += deslocamentos[texto[t+1]];
    }
    return -1;
}

