#include <stdlib.h>
#include <stdio.h>
#include "exerc3_lista1_prog.h"

int main(void) {
    Ponto p1, p2, p;

    printf("Digite as coordenadas do ponto 1 (na forma x,y): ");
    scanf("%lf,%lf", &p1.x, &p1.y);
    printf("Agora, as coordenadas do ponto 2 (x,y): ");
    scanf("%lf,%lf", &p2.x, &p2.y);

    printf("Digite a coordenada y do ponto em questao: ");
    scanf("%lf", &p.y);

    if (p1.x == p2.x) { // alinhados verticalmente?
        p.x = p1.x;     // o outro ponto estarah na mesma reta vertical
    } else {
        p.x = (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
    }
    printf("A coordenada x correspondente vale %lf.\n", p.x);

    return EXIT_SUCCESS;
}

