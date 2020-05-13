/* n! = 1.2.3...(n-2)(n-1)n */

unsigned fatorial_i(unsigned n) {
    //      (E) (L)                                                 --> 2
    unsigned f = 1; // inicializacao do fatorial
    //      (E) (L)                                                 --> 2
    unsigned i = 1; // primeiro termo da multiplicacao
    //    (L) (C)(L) executado (n+1) vezes (n verdadeiras e 1 falsa)--> 3(n+1)
    while (i  <=  n) {
    // (E) (L) (A) (L)                                              --> 4n
        f = f   *   i;  // f *= i;
    // (E) (L) (A) (L)                                              --> 4n
        i = i   +   1;  // ++i;
    }
    // (R) (L)                                                      --> 2
    return  f;
}                                                   // -----------------------
                                                    // T(n) = 11n + 9
                                                    // Complexidade O(n) linear
/*       | 1, se n = 0 (por definicao, 0! = 1)
 * n! = <
 *       | n.(n-1)!, caso contrario
 */


unsigned fatorial_r(unsigned n) {
    // (L) (C)(L)                                   --> 3
    if (n  ==  0) {
    //  (R)   (L)                                   --> 2 (*)
        return 1;
    } else {
    //  (R)   (L) (A)  T(n-1)    (L) (A) (L)        --> 6 + T(n-1) (**)
        return n   *   fatorial_r(n   -   1);
    }
}

// (*) soh vai ser executada UMA vez, quando n = 0
// (**) vai ser executada todas as outras vezes, quando n > 0

/*         | 5, se n = 0
 * T(n) = <
 *         | T(n-1) + 9, caso contrario
 */

/* T(n) = T(n-1) + 9
 *      = [ T(n-2) + 9 ] + 9
 *      = { [ T(n-3) + 9 ] + 9 } + 9
 *      = ...
 *      = T(n-i) + 9i --> formula geral
 *
 *      Qual o valor de i para que (n-i) seja 0, e portanto T(n-i) = 5? R.:i=n
 *
 * T(n) = T(n-n) + 9n
 *      = T(0) + 9n
 *      = 5 + 9n
 * T(n) = 9n + 5 <-- Funcao de complexidade
 *               <-- Ordem de complexidade O(n) -> linear
 */
