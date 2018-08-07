#include <stdlib.h>
#include <stdio.h>
#include "generico.h"
#include "pilha.h"

struct ponto {
    float coord_x, coord_y;
};

void imprime_char(void* pc) {
    char* pchar = pc;
    putchar(*pchar);
}

void imprime_int(void* pi) {
    printf("%d", *((int*)pi) );
}

void imprime_double(void* pd) {
    printf("%e", *((double*)pd) );
}

void imprime_string(void* ps) {
    printf("%s", (char*) ps);
}

void imprime_ponto(void* pp) {
    struct ponto* pponto = pp;
    printf("(%.2f, %.2f)", pponto->coord_x, pponto->coord_y);
}

int main(int argc, char* argv[]) {
    char c = 'A';
    int d = 88;
    double avo = 6.023e+23;
    char s[] = "abacate";
    struct ponto pto = { 1.5, 2.875 };

    Pilha* p = NULL;    // pilha nao existe (ainda)!
    p = cria();

    if (underflow(p)) {
        puts("Pilha vazia, como esperado...");
    } else {
        puts("Vixi, deu xabu...");
        destroi(p);
        return EXIT_FAILURE;
    }

    // Empilha o caractere
    generico g = {
        .coisa = &c,
        .imprime = &imprime_char
    };
    push(p, &g);

    // Empilha o inteiro
    g.coisa = &d;
    g.imprime = &imprime_int;
    push(p, &g);

    // Continua com os outros tipos...
    g.coisa = &avo;
    g.imprime = &imprime_double;
    push(p, &g);

    g.coisa = s;
    g.imprime = &imprime_string;
    push(p, &g);

    g.coisa = &pto;
    g.imprime = &imprime_ponto;
    push(p, &g);

    // Imprime a pilha
    imprime(p);
    putchar('\n');

    // Tira um elemento da pilha:
    generico* pg = pop(p);

    // Pra conferir o que foi tirado, imprimo esse elemento
    printf("Elemento: ");
    pg->imprime(pg->coisa);
    putchar('\n');
    free(pg);   // pop aloca, eu libero...

    destroi(p);

    EXIT_SUCCESS;
}

