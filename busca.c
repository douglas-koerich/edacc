#include "busca.h"

unsigned insucessos = 0;

int sequencial(const Registro* v, size_t n, int x) {
    int i = 0;
    while (i < n) {
        if (v[i].chave == x) {
            return i; // chave encontrada
        }
        ++i, ++insucessos;
    }
    return -1; // chave inexistente
}

int binaria(const Registro* v, int i, int s, int x) {
    if (i > s) { // segmento nulo do vetor
        return -1; // chave inexistente
    }
    int m = (i + s) / 2; // calcula a posicao de meio do vetor
    if (v[m].chave == x) { // compara com o meio do vetor
        return m; // chave encontrada
    }
    ++insucessos;
    if (v[m].chave > x) { // decide por qual metade continuar (recursivamente)
        return binaria(v, i, m-1, x);
    } else {
        return binaria(v, m+1, s, x); 
    }
}

int interpolacao(const Registro* v, int i, int s, int x) {
    if (i > s) { // segmento nulo do vetor
        return -1; // chave inexistente
    }
    // Na busca por interpolacao, procura-se determinar a distancia da posicao
    // que contem chave procurada ao inicio do vetor, considerando que essa
    // distancia eh PROPORCIONAL ah diferenca entre o valor do chave e o valor
    // armazenado na posicao inicial
    int distancia_valor = x - v[i].chave,
        distancia_total_valor = v[s].chave - v[i].chave,
        distancia_total_indices = s - i;
    int distancia_indices = distancia_total_valor > 0?
                            (float) distancia_total_indices * distancia_valor / distancia_total_valor:
                            0;
    int p = i + distancia_indices; // aplica a distancia em relacao ao inicio
    if (v[p].chave == x) { // compara com a chave nessa posicao do vetor
        return p; // chave encontrada
    }
    ++insucessos;
    if (v[p].chave > x) { // decide por qual secao continuar (recursivamente)
        return interpolacao(v, i, p-1, x);
    } else {
        return interpolacao(v, p+1, s, x); 
    }
}
