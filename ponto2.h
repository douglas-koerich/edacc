#ifndef PONTO_H
#define PONTO_H

struct ponto {
    float x, y;
};
typedef struct ponto ponto;

float coord_x(const struct ponto* p1, const struct ponto* p2, float y);

#endif