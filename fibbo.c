#include <stdlib.h>
#include <stdio.h>

int fibbo_ite(int);
int fibbo_rec(int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero invalido de parametros");
        return EXIT_FAILURE;
    }
    int ordem = atoi(argv[1]);

    printf("O %d-esimo numero de Fibonacci eh %d\n", ordem, fibbo_ite(ordem));
    printf("Repetindo, o numero eh %d\n", fibbo_rec(ordem));

    return EXIT_SUCCESS;
}

int fibbo_ite(int ordem) {
    if (ordem < 3) {
        return ordem;
    }
    else {
        int ant_ant = 1, ant = 2;
        int contador = 2;   // numero de termos anteriores (2)
        int fibbo;
        do {
            fibbo = ant_ant + ant;
            ant_ant = ant;
            ant = fibbo;
            ++contador;
        } while (contador < ordem);
        return fibbo;
    }
}

int fibbo_rec(int ordem) {
    if (ordem < 3) {
        return ordem;
    }
    else {
        return fibbo_rec(ordem-1) + fibbo_rec(ordem-2);
    }
}

