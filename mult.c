#include <stdlib.h>
#include <stdio.h>

long long mult(long long, long long);

int main(void) {
    long long A, B, M;

    printf("Digite o valor de A: ");
    scanf("%lld", &A);
    printf("Digite o valor de B: ");
    scanf("%lld", &B);

    M = mult(A, B);

    printf("O produto dos valores eh %lld.\n", M);

    return EXIT_SUCCESS;
}

#ifndef RECURSIVO
long long mult(long long A, long long B) {
    long long S, n;
    for (S=0, n=1; n<=B; ++n) {
        S += A;
    }
    return S;
}
#else
long long mult(long long A, long long B) {
    if (B == 0) {
        return 0;
    }
    else {
        return A + mult(A, B-1);
    }
}
#endif

