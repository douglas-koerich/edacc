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
    //    (R) ------------------------------> 1
    if (i == s) { // condicao terminal
        // (M)  (D) ------------------------> 2
        return A[i];
    } else { // fase ativa
        int m, maior1, maior2;
        // (M) (A) (A) ---------------------> 3
        m = (i + s) / 2;
        //    (M)   (*) --------------------> 1 + T(n/2)
        maior1 = maxVetor_(A, i, m);
        //    (M)   (*)       (A) ----------> 2 + T(n/2)
        maior2 = maxVetor_(A, m+1, s);
        //        (R) ----------------------> 1
        if (maior1 > maior2) {
            // (M) -------------------------> 1
            return maior1;
        } else {
            // (contabiliza if OU else) ----> X
            return maior2;
        }
    } // -----------------------------------> ==================
} // ---------------------------------------> T(n) = 9 + 2T(n/2)

/* Equacao de recorrencia:
        | 3, se n = 1 (*condicao terminal*)
T(n) = <
        | 2T(n/2) + 9, se n > 1 (*fase ativa*)

   Resolucao pelo metodo da expansao telescopica (busca pela formula geral):
   T(n) = 2[T(n/2)] + 9
        = 2[2{T(n/4)} + 9] + 9
        = 2[2{2T(n/8) + 9} + 9] + 9
        = ...
        = 2^i.T(n/2^i) + 9(1 + 2 + 4 + ... + 2^i) ==> FORMULA GERAL (provisoria)

   A soma (1 + 2 + 4 + ... + 2^(i-1)) eh o somatorio de uma PG, onde: a1 = 1;
   q = 2; e n = i (expoentes de 2 indo de 0 a i-1)
   S = a1.(q^n - 1)/(q - 1) = 1.(2^i - 1)/(2 - 1) = 2^i - 1

   Entao: T(n) = 2^i.T(n/2^i) + 9(2^i - 1) ==> Eq. de recorrencia GEOMETRICA

   Se a formula eh geral, pode-se concluir que T(n/2^i) chegarah ah condicao
   T(1) em algum momento, no qual: n/2^i = 1, portanto quando 2^i = n
   Substituindo:

   T(n) = n.T(n/n) + 9(n - 1)
        = n.T(1) + 9(n-1) = 3n + 9n - 9

   Expressao final:
   T(n) = 12n - 9 =====> FUNCAO DE COMPLEXIDADE, portanto o algoritmo eh O(n)
*/

int maxVetor(const int A[], size_t n) {
    return maxVetor_(A, 0, n-1);
}