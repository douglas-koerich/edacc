/* 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
   ^  ^  ^  ^
   |  |  |  |
   |  |  |  termo de ordem 3
   |  |  termo de ordem 2
   |  termo de ordem 1
   termo de ordem 0
*/

#include <stdlib.h>
#include <stdio.h>

unsigned fibonacci(unsigned ordem) {
    /* Versao iterativa
    if (ordem < 2) {
        return ordem;
    }
    unsigned f_n, // numero da vez
             f_n_ant = 1, // numero anterior ao da vez
             f_n_ant_ant = 0; // numero anterior ao anterior

    unsigned o;
    for (o = 2; o <= ordem; ++o) {
        f_n = f_n_ant + f_n_ant_ant;
        f_n_ant_ant = f_n_ant;
        f_n_ant = f_n;
    }
    return f_n;
    */
    
    /* Versao recursiva */
    if (ordem < 2) {
        return ordem;
    } else {
        return fibonacci(ordem-1) + fibonacci(ordem-2);
    }
    /**/
}

int main(void) {
    unsigned ordem;
    printf("Qual eh a ordem do numero de Fibonacci desejado (>= 0)? ");
    scanf("%u", &ordem);

    unsigned fibo = fibonacci(ordem);
    printf("O numero eh %u\n", fibo);

    return EXIT_SUCCESS;
}