#include <stdlib.h>
#include <stdio.h>

int maxVetor(const int A[], size_t n);

#define TAMANHO 10

int main(void) {
    int exemplo[TAMANHO] = { 4, 7, 3, 9, 2, 1, 6, -2, 0, -4 };
    printf("O maior valor armazenado no vetor eh %d\n",
           maxVetor(exemplo, TAMANHO));
    return EXIT_SUCCESS;
}

/* IMPLEMENTACAO ITERATIVA (COM LACO/REPETICAO)
int maxVetor(const int A[], size_t n) {
    //            (M) (D) ------------> 2
    int maiorValor = A[0];
    int i;
    //    (M)    (R)   (M+A) ---------> 1 + (n+1) + 2n
    for (i = 0; i < n; ++i) {
        //   (D)(R) ------------------> 2n
        if (A[i] > maiorValor) {
            //        (M) (D) --------> 2n
            maiorValor = A[i];
        }
    }
    // (M) ---------------------------> 1
    return maiorValor;
} // ---------------------------------> ===============
// -----------------------------------> T(n) = 7n + 5
*/

#if 0
// VERSAO RECURSIVA
int maxVetor(const int A[], size_t n) {
    //    (R) --------------------------------------> 1
    if (n == 1) { // condicao terminal da recursao
        // (R)  (D) --------------------------------> 2
        return A[0];
    } else { // fase ativa da recursao
        //            (M)  (*)       (A) -----------> 2 + T(n-1)
        int maiorValor = maxVetor(A, n-1);

        //   (A+D)(R) ------------------------------> 3
        if (A[n-1] > maiorValor) {
            //        (M) (A+D) --------------------> 3
            maiorValor = A[n-1];
        }
        // (M) -------------------------------------> 1
        return maiorValor;
    } // -------------------------------------------> ======
} // -----------------------------------------------> T(n) = 10 + T(n-1) *ativa*

/* Equacao de recorrencia:
        | 3, se n = 1 (*condicao terminal*)
T(n) = <
        | T(n-1) + 10, se n > 1 (*fase ativa*)

   Resolucao pelo metodo da expansao telescopica (busca pela formula geral):
   T(n) = [T(n-1)] + 10
        = [{T(n-2)} + 10] + 10
        = [{T(n-3) + 10} + 10] + 10
        = ...
        = T(n-k) + k.10 =====> FORMULA GERAL (Equacao de recorrencia LINEAR)

   Se a formula eh geral, pode-se concluir que T(n-k) chegarah ah condicao T(1)
   em algum momento, no qual: n-k = 1, portanto quando k = n-1
   Substituindo:

   T(n) = T(n - (n-1)) + (n-1).10
        = T(1) + 10(n-1) = 3 + 10n - 10

   Expressao final:
   T(n) = 10n - 7 =====> FUNCAO DE COMPLEXIDADE, portanto o algoritmo eh O(n)
*/
#endif

int maxVetor_(const int A[], int i, int s) {
    if (i == s) { // condicao terminal
        return A[i];
    } else {
        int m = (i + s) / 2;
        int maior1 = maxVetor_(A, i, m);
        int maior2 = maxVetor_(A, m+1, s);
        if (maior1 > maior2) {
            return maior1;
        } else {
            return maior2;
        }
    }
}

int maxVetor(const int A[], size_t n) {
    return maxVetor_(A, 0, n-1);
}