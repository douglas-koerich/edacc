#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "generico2.h"
#include "fila.h"

struct ponto {
    float coord_x, coord_y;
};

void imprime_char(void* pc) {
    char* pchar = pc;
    putchar(*pchar);
}

int compara_char(void* pc1, void* pc2) {
    char* pchar1 = pc1;
    char* pchar2 = pc2;
    if (*pchar1 == *pchar2) {
        return 0;
    } else if (*pchar1 > *pchar2) {
        return 1;
    } else {
        return -1;
    }
}

void imprime_int(void* pi) {
    printf("%d", *((int*)pi) );
}

int compara_int(void* pi1, void* pi2) {
    char* pint1 = pi1;
    char* pint2 = pi2;
    if (*pint1 == *pint2) {
        return 0;
    } else if (*pint1 > *pint2) {
        return 1;
    } else {
        return -1;
    }
}

void imprime_double(void* pd) {
    printf("%e", *((double*)pd) );
}

int compara_double(void* pd1, void* pd2) {
    double* pdoub1 = pd1;
    double* pdoub2 = pd2;
    if (*pdoub1 > *pdoub2) {
        return 1;
    } else if (*pdoub1 < *pdoub2) {
        return -1;
    } else {
        return 0;
    }
}

void imprime_string(void* ps) {
    printf("%s", (char*) ps);
}

int compara_string(void* ps1, void* ps2) {
    return strcmp((const char*) ps1, (const char*) ps2);
}

void imprime_ponto(void* pp) {
    struct ponto* pponto = pp;
    printf("(%.2f, %.2f)", pponto->coord_x, pponto->coord_y);
}

int compara_ponto(void* pp1, void* pp2) {
    struct ponto* ppto1 = pp1;
    struct ponto* ppto2 = pp2;
    if (ppto1->coord_x < ppto2->coord_x) {
        return -1;
    } else if (ppto1->coord_x > ppto2->coord_x) {
        return 1;
    } else if (ppto1->coord_y < ppto2->coord_y) {
        return -1;
    } else if (ppto1->coord_y > ppto2->coord_y) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    char c = 'A';
    int d = 88;
    double avo = 6.023e+23;
    char s[] = "abacate";
    struct ponto pto = { 1.5, 2.875 };

    Fila* f = NULL;    // fila nao existe (ainda)!
    f = cria();

    if (underflow(f)) {
        puts("Fila vazia, como esperado...");
    } else {
        puts("Vixi, deu xabu...");
        destroi(f);
        return EXIT_FAILURE;
    }

    // Enfileira o caractere
    generico g = {
        .coisa = &c,
        .imprime = &imprime_char,
        .compara = &compara_char
    };
    enqueue(f, &g);

    // Enfileira o inteiro
    g.coisa = &d;
    g.imprime = &imprime_int;
    g.compara = &compara_int;
    enqueue(f, &g);

    // Continua com os outros tipos...
    g.coisa = &avo;
    g.imprime = &imprime_double;
    g.compara = &compara_double;
    enqueue(f, &g);

    g.coisa = s;
    g.imprime = &imprime_string;
    g.compara = &compara_string;
    enqueue(f, &g);

    g.coisa = &pto;
    g.imprime = &imprime_ponto;
    g.compara = &compara_ponto;
    enqueue(f, &g);

    // Imprime a fila
    imprime(f);
    putchar('\n');

    // Tira um elemento da fila:
    generico* pg = dequeue(f);

    // Pra conferir o que foi tirado, imprimo esse elemento
    printf("Elemento: ");
    pg->imprime(pg->coisa);
    putchar('\n');
    free(pg);   // pop aloca, eu libero...

    destroi(f);

    EXIT_SUCCESS;
}
