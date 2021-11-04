#include <stdlib.h>
#include <stdio.h>

/* Versao "pedra" do algoritmo:
void bolha(int* v, size_t n) {
    int i;
    for (i = 1; i < n; ++i) {
        int j;
        printf("%da. varredura:\n", i);
        for (j = 0; j < n-i; ++j) {
            if (v[j] > v[j+1]) {
                int x = v[j];
                v[j] = v[j+1];
                v[j+1] = x;
            }
            // EXTRA: imprime o vetor para acompanhar o algoritmo
            int k;
            for (k = 0; k < n; ++k) {
                printf("%d ", v[k]);
            }
            putchar('\n');
        }
    }
}
*/

void bolha(int* v, size_t n) {
    int i;
    //    (M)    (R)  (M+A) -------------------> n
    for (i = 1; i < n; ++i) {
        int j;
        // printf("%da. varredura:\n", i);
        //    (M)(A)   (R)    (M+A) -----------> n(n-1) = n² - n
        for (j = n-1; j >= i; --j) {
            //   (D)(R) (D+A) -----------------> 4(n-1)(n-1) = 4n² - 8n + 4
            if (v[j] < v[j-1]) {
                //   (M) (D) ------------------> 2(n-1)(n-1) = 2n² - 4n + 2
                int x = v[j];
                // (D)(M)(D+A) ----------------> 4(n-1)(n-1) = 4n² - 8n + 4
                v[j] = v[j-1];
                // (D+A)(M) -------------------> 3(n-1)(n-1) = 3n² - 6n + 3
                v[j-1] = x;
            }
            /*
            // EXTRA: imprime o vetor para acompanhar o algoritmo
            int k;
            for (k = 0; k < n; ++k) {
                printf("%d ", v[k]);
            }
            putchar('\n');
            */
        }
    } // --------------------------------------> =================
} // ------------------------------------------> T(n) = 14n² - 26n + 13
// --------------------------------------------> O(n²) -> quadratica
