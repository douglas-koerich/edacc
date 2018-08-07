#include <stdlib.h>
#include <stdio.h>

int mul_i(int, int);    // iterativa
int mul_r(int, int);    // recursiva

int main(void) {
    printf("Digite 2 numeros para multiplicar: ");
    int n, m;
    scanf("%d %d", &n, &m);

    printf("Multiplicacao iterativa = %d\n", mul_i(n, m));
    printf("Multiplicacao recursiva = %d\n", mul_r(n, m));

    return EXIT_SUCCESS;
}

int mul_i(int n, int m) {
    int s = n;
    while (m > 1) {
        s += n;
        --m;
    }
    return s;
}

int mul_r(int n, int m) {
    if (m == 1) {                           // CONDICAO TERMINAL: necessaria para interromper a recursao
        return n;   // nao ha soma a fazer  // nao ha chamada a mesma funcao mul_r
    } else {                                // FASE ATIVA DA RECURSAO: chamadas consecutivas de mul_r
        return n + mul_r(n, m-1);
    }
}
