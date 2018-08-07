#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ponto.h"

#define NUM_PONTOS 2

int main(void) {
    float distancia, dist_origem;
    struct ponto p1;
    point p2;
    const struct ponto ORIGEM = { 0.0, 0.0 };
    // Em C11, ... ORIGEM = { .x = 0.0, .y = 0.0 };

    // Uma lista (vetor) de pontos
    struct ponto vetor[NUM_PONTOS];
    
    // Leitura dos pontos
    printf("Digite as coordenadas x,y do primeiro ponto: ");
    scanf("%f,%f", &p1.x, &p1.y);
    printf("Digite as coordenadas x,y do segundo ponto: ");
    scanf("%f,%f", &p2.x, &p2.y);

    float quad_dif_x, quad_dif_y;
    quad_dif_x = pow(p2.x - p1.x, 2);
    quad_dif_y = pow(p2.y - p1.y, 2);

    distancia = sqrt(quad_dif_x + quad_dif_y);
    printf("A distancia em linha reta entre os pontos eh %.2f\n", distancia);

    quad_dif_x = pow(p2.x - ORIGEM.x, 2);
    quad_dif_y = pow(p2.y - ORIGEM.y, 2);
    dist_origem = sqrt(quad_dif_x + quad_dif_y);
    printf("A distancia do segundo ponto ateh a origem eh %.2f\n", dist_origem);

    // Preenchendo o vetor...
    printf("Digite as coordenadas x,y do primeiro ponto NO VETOR: ");
    scanf("%f,%f", &vetor[0].x, &vetor[0].y);
    printf("Digite as coordenadas x,y do segundo ponto NO VETOR: ");
    scanf("%f,%f", &vetor[1].x, &vetor[1].y);

    float y_qualquer;
    printf("Digite uma coordenada y qualquer: ");
    scanf("%f", &y_qualquer);
    float x = coord_x(vetor[0], vetor[1], y_qualquer);
    printf("A coordenada x do ponto cuja coordenada y eh %.2f e que "
           "estah na mesma reta dos pontos do vetor eh %.2f\n", y_qualquer, x);

    return EXIT_SUCCESS;
}

float coord_x(struct ponto p1, struct ponto p2, float y) {
    float x;
    x = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
    return x;
}

