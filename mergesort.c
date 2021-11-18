#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void merge(int* v, int p, int u) {
    /*
    // EXTRA: imprime o segmento do vetor antes das chamadas recursivas
    int j;
    for (j = p; j <= u; ++j) {
        printf("%d ", v[j]);
    }
    putchar('\n');
    */
    //    (R) ---------------------------------------------------> 1
    if (p == u) { // vetor de tamanho unitario
        // (M) --------------------------------------------------> 1
        return;   // (primeiro indice = ultimo indice)
    }
    //   (M)  (A)  (A) ------------------------------------------> 3
    int m = (p + u) / 2;

    // (T) ------------------------------------------------------> T(n/2)
    merge(v, p, m);     // ordena metade inferior
    // (T)   (A) ------------------------------------------------> T(n/2) + 1
    merge(v, m+1, u);   // ordena metade superior

    // Eh necessario intercalar as duas metades jah ordenadas
    //      (M)  (A) (A) ----------------------------------------> 3
    size_t n = (u - p + 1);
    //    (M)  (M)             (A) ------------------------------> 3
    int* w = malloc(sizeof(int) * n);
    //   (M)    (M)(A)   (M) ------------------------------------> 4
    int e = p, d = m+1, i = 0;
    //       (R)  (R)  (R) --------------------------------------> 3.(n/2 + 1)
    while (e <= m && d <= u) { // enquanto ha dois valores a comparar
        //  (D) (R) (D) -----------------------------------------> 3.(n/2)
        if (v[e] < v[d]) {
        // (D+A+M)(M)(D+A+M) ------------------------------------> 7.(n/2)
            w[i++] = v[e++];
        } else { // ----- conta o "if" OU o "else" --------------> 0 (**)
            w[i++] = v[d++];
        }
    }
    //       (R) ------------------------------------------------> n/2 + 1
    while (e <= m) { // no caso da metade inferior nao ter sido finalizada
    // (D+A+M)(M)(D+A+M) ----------------------------------------> 7.n/2
        w[i++] = v[e++];
    }
    //       (R) --- no pior caso, esta condicao ja retorna false ---> 1
    while (d <= u) { // no caso da metade superior nao ter sido finalizada
    // ----------------------------------------------------------> 0
        w[i++] = v[d++];
    }
    // (M)  (D)                 (A) -----------------------------> 3
    memcpy(&v[p], w, sizeof(int) * n);
    // (M) ------------------------------------------------------> 1
    free(w);
    /*
    // EXTRA: imprime o segmento do vetor depois da intercalacao
    for (j = p; j <= u; ++j) {
        printf("%d ", v[j]);
    }
    putchar('\n');
    */
    // ----------------------------------------> ==========================
    //                                           EQUACAO DE RECORRENCIA:
    //                                           T(n) = 2, se n = 1
    //                                                = 2.T(n/2) + 21.n/2 + 24 
}

/*
Resolvendo a equacao de recorrencia pelo metodo da expansao telescopica:
T(n) = 2{T(n/2)} + 21n/2 + 24
     = 2{2[T(n/4)] + 21n/4 + 24} + 21n/2 + 24
     = 2{2[2T(n/8) + 21n/8 + 24] + 21n/4 + 24} + 21n/2 + 24
     = ...
     = 2^i.T(n/(2^i)) + 21n/2.i + 24(1 + 2 + 4 + ... + 2^(i-1))
                                    /--- Soma de uma P.G. ----/

     Soma da PG: a1(q^n - 1) / (q - 1), onde a1 = 1, q = 2, n = i:

T(n) = 2^i.T(n/(2^i)) + 21n/2.i + 24.(2^i - 1)
     = 2^i.T(n/(2^i)) + 21n/2.i + 24.2^i - 24 (EXPRESSAO GERAL)

Se a expressao eh GERAL, vale tambem para quando T(n/(2^i)) = T(1) = 2, entao
vale para 2^i = n (i = lg(n)), o que faz T(n/n) = T(1) = 2.
Substituindo:

T(n) = n.T(n/n) + (21n/2).lg(n) + 24n - 24
     = n.T(1) + 21n.lg(n)/2 + 24n - 24
     = 2n + 21n.lg(n)/2 + 24n - 24
     = 21n.lg(n) + 26n - 24 (FUNCAO DE COMPLEXIDADE)
     --> Complexidade O(n.lg(n))
*/