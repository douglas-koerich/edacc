#include "registro.h"

void quicksort(R vetor[], int inf, int sup) {
    //  (L) (C) (L)  ==> 3
    if (inf >= sup) {
        // (R) ==> 1
        return;
    }
    //                    ---------------(L)-----------------
    //                    ------------(L)------------(I) (L)
    //       (E)          (L) (I) (L) (A) (L) (A)(L)   
    unsigned chave_pivo = vetor[ (inf  +  sup) /  2  ].chave; // ==> 12
    //  (E)   (L)  (E)   (L) ==> 4
    int esq = inf, dir = sup;
    //     (L) (C)(L) * n/2
    while (esq <= dir) {
        //     ------(L)------ (C)   (L)
        //     ---(L)---(I)(L)
        //     (L)(I)(L)
        while (vetor[esq].chave < chave_pivo) // ==> 9 * n/2
            ++esq; // esq = esq + 1; ==> 4 * n/2
        while (vetor[dir].chave > chave_pivo) // ==> 9 * n/2
            --dir; // ==> 4 * n/2
        if (esq <= dir) { // ==> 3 * n/2
            TROCA(vetor+esq, vetor+dir); // ==> X * n/2
            ++esq, --dir; // ==> 8 * n/2
        }
    }
    // T(n/2) (L)    (L)  (L)
    quicksort(vetor, inf, dir);
    // T(n/2) (L)    (L)  (L)
    quicksort(vetor, esq, sup);
}

// T(n) = 4, se n igual a 1
//      = 2T(n/2) + A*n/2 + B
//      ...
//      = a.nlgn + ...
// Ordem de complexidade = O(nlgn)
