#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listad.h"

int main() {
    srand((unsigned) time(0));
    tipo n;

    struct Lista* l = cria();

    int i;
    puts(">>> Montando uma lista com pares no fim, impares no inicio <<<");
    for (i=1; i<=15; ++i) {
        tipo n = rand() % 1000;
        if (n % 2 == 0) {
            inserirFim(l, n);
        }
        else {
            inserirInicio(l, n);
        }
        imprime(l);
    }
    puts(">>> Inserindo elementos em posicoes determinadas (3 e 13) <<<");
    inserirPosicao(l, 1003, 3);
    inserirPosicao(l, 1013, 13);
    imprime(l);

    puts(">>> Digite um numero para buscar na lista <<<");
    tipo x;
    scanf("%u", &x);
    tipo* onde = busca(l, x);
    if (onde == NULL) {
        puts("Nao encontrei o valor na lista");
    }
    else {
        printf("Encontrei o valor no endereco %p\n", onde);
    }

    puts(">>> Removendo de uma posicao especifica (5) <<<");
    removerPosicao(l, &n, 5);
    imprime(l);

    puts(">>> Removendo um valor especifico (1013) <<<");
    size_t pos;
    removerValor(l, 1013, &pos);
    imprime(l);

    puts(">>> Removendo o elemento do inicio <<<");
    removerInicio(l, &n);
    imprime(l);

    puts(">>> Removendo o elemento do fim <<<");
    removerFim(l, &n);
    imprime(l);

    puts(">>> Imprime no sentido inverso <<<");
    imprime_r(l);

    destroi(l);

    return 0;
}

