#include <stdlib.h>
#include <stdio.h>
#include "ponto.h"

struct Ponto {
    double x, y;
};

Ponto* aloca_pontos(size_t num) {
    return malloc(sizeof(Ponto) * num);
}

Ponto* proximo_ponto(Ponto* base) {
    return base+1;
}

void le_ponto(Ponto* ponto) {
    printf("Digite a ordenada (X): ");
    scanf("%lf", &ponto->x);
    printf("Digite a abscissa (Y): ");
    scanf("%lf", &ponto->y);
}

void imprime_ponto(void* p) {
    if (NULL == p) {
        printf("(--BAD--,--BAD--)");
        return;
    }
    Ponto* ponto = (Ponto*) p;
    printf("(%.5lf,%.5lf)", ponto->x, ponto->y);
}

bool compara_pontos(void* p1, void* p2) {
    if (NULL == p1) {
        if (NULL == p2) {
            return true;
        }
        return false;
    } else if (NULL == p2) {
        return false;
    }
    Ponto* ponto_1 = (Ponto*) p1;
    Ponto* ponto_2 = (Ponto*) p2;
    if (ponto_1->x == ponto_2->x && ponto_1->y == ponto_2->y) {
        return true;
    }
    return false;
}

