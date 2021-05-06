#include <stdlib.h>
#include <stdio.h>

unsigned fact(unsigned);

int main(void) {
    unsigned n;
    printf("Digite um numero inteiro e positivo: ");
    scanf("%u", &n);

    unsigned f = fact(n);
    printf("O fatorial do numero eh %u\n", f);

    return EXIT_SUCCESS;
}

/*
// fact(n) = n! = n x (n-1) x (n-2) x ... x 3 x 2 x 1
// Por definicao: 0! = 1

unsigned fact(unsigned n) {
    unsigned produto = 1, i;
    for (i = 1; i <= n; ++i) {
        produto *= i;
    }
    return produto;
}
*/

// fact(n) = n! = n x (n-1) x (n-2) x ... x 3 x 2 x 1
//         = n! = n x (n-1)!
//                    (n-1)! = (n-1) x (n-2)!
// Se n for igual a zero, a solucao eh trivial (retorna 1)

//                 | n x (n-1)!, se n > 0
// fact(n) = n! = <  ou
//                 | 1 , se n = 0

unsigned fact(unsigned n) {
    if (n == 0) {   // condicao terminal
        return 1;   // solucao basica
    } else {                    // fase ativa
        return n * fact(n-1);   // chamada recursiva
    }
}