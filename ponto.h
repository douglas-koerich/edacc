#ifndef PONTO_H
#define PONTO_H

// DEFINICAO (nao ocupa memoria, pois nao eh uma variavel) de tipo
struct ponto {
    // Campos da estrutura
    float x; // float x, y;
    float y;
};
typedef struct ponto point;

/*
 * typedef struct ponto {
 *     float x, y;
 * } point;
 */

// Prototipo da funcao que retorna a coordenada x do ponto cujo y
// estah na mesma reta que os pontos (x1, y1) e (x2, y2)
float coord_x(struct ponto p1, struct ponto p2, float y);

#endif

