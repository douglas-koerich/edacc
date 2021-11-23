#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

unsigned contador = 0;

static bool compara(int a, int b) {
    ++contador;
    return a == b;
}

int sequencial(int* v, size_t n, int x) {
    int i;
    for (i = 0; i < n; ++i) {
        // if (v[i] == x) {
        if (compara(v[i], x)) {
            return i;
        }
    }
    return -1; // indice invalido
}

int binaria(int* v, int p, int u, int x) {
    if (p > u) { // recursao conduziu a um vetor de tamanho "negativo"
        return -1; // indice invalido para uma busca sem sucesso
    }
    int m = (p + u) / 2;
    if (compara(v[m], x)) {
        return m;
    }
    if (x < v[m]) {
        return binaria(v, p, m-1, x);
    } else {
        return binaria(v, m+1, u, x);
    }
}

int interpolacao(int* v, int p, int u, int x) {
    if (p > u) {
        return -1;
    }
    int dtc = v[u] - v[p],  // distancia total entre chaves
        dti = u - p,        // distancia total entre indices
        dc = x - v[p];      // distancia para a chave procurada
        // di = i - p;      // distancia para a indice procurado
    /*
    dc ---> di
    dtc --> dti
    */
    int i = dtc == 0? p: (dc * dti / dtc + p); // testa para nao dividir por 0
    if (i < p || i > u) { // indice presumido fora dos limites do vetor
        return -1;
    }
    if (compara(v[i], x)) {
        return i;
    }
    if (x < v[i]) {
        return interpolacao(v, p, i-1, x);
    } else {
        return interpolacao(v, i+1, u, x);
    }
}

