#include <stdlib.h>
#include <stdio.h>
#include "ponto.h"

#define NUM_PONTOS 2

int main(void) {
    /*
    struct ponto vetor[NUM_PONTOS]; // alocacao estatica do vetor
    struct ponto* p_ponto = vetor; // copia endereco do vetor para um ponteiro
    */
    struct ponto* p1 = malloc(sizeof(struct ponto)); // alocacao dinamica de uma estrutura singular
    struct ponto* vetor = malloc(NUM_PONTOS * sizeof(struct ponto)); // alocacao dinamica do vetor

    printf("Digite x,y do primeiro ponto: ");
    scanf("%f,%f", &vetor[0].x, &vetor[0].y);

    printf("Digite x,y do segundo ponto: ");
    // scanf("%f,%f", &vetor[1].x, &vetor[1].y);
    scanf("%f,%f", &((vetor+1)->x), &((vetor+1)->y)); // & continua para apontar pros campos!

    float y_qualquer;
    float* pont_y = &y_qualquer;

    printf("Digite uma coordenada y: ");

    // scanf("%f", &y_qualquer);
    scanf("%f", pont_y);

    float x = coord_x(&vetor[0], vetor+1, y_qualquer);
    printf("x = %.2f\n", x);

    free(vetor); // nao deixa blocos perdidos em memoria
    free(p1);

    return EXIT_SUCCESS;
}

float coord_x(const struct ponto* p1, const struct ponto* p2, float y) {
    float x;
    x = (y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + p1->x;
    return x;
}
