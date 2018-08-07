#include <stdlib.h>
#include <stdio.h>

int MDC(int, int);

int main(void) {
    int n, m;

    printf("Digite o valor de n: ");
    scanf("%d", &n);
    printf("Digite o valor de m: ");
    scanf("%d", &m);

    int x = MDC(n, m);

    printf("O maximo divisor comum entre %d e %d eh %d.\n", n, m, x);

    return EXIT_SUCCESS;
}

int MDC(int n, int m) {
    if (m <= n && n % m == 0) {
        return m;
    }
    if (n <= m) {
        return MDC(m, n);
    }
    return MDC(m, n % m);
}

