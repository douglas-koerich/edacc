#include <stdlib.h>
#include "registro.h"

void bolha(R vetor[], size_t n) {
    int j;
    //  |--1--||--n+1--| |----n-----|
    //  (E) (L)(L)(C)(L) (E)(L)(A)(L) ==> 2*1 + 3*(n+1) + 4*n = 7n + 5 
    for (j = 1; j <=  n; ++j) { // deve passar pelo vetor o numero de vezes
                               // igual ao seu tamanho para garantir o pior caso
        int i;
        //  |----------------n----------------|
        //  |-----1-----||--n+1--| |----n-----|
        //  (E) (L)(A)(L)(L)(C)(L) (E)(L)(A)(L) ==> 4*1*n + 3*(n+1)*n + 4*n*n = 7n^2 + 7n
        for (i = n  -  1; i  >  0; --i) {
            // ...
            if (vetor[i].chave < vetor[i-1].chave) { // fora de ordem numa
                                                     // classificacao CRESCENTE
                TROCA(vetor+i, vetor+i-1);
            }
        }
    }
}

// Ordem de complexidade O(n^2)
