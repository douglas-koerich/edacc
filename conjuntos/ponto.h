#ifndef PONTO_H
#define PONTO_H

#include <stdbool.h>

struct Ponto;
typedef struct Ponto Ponto;

Ponto* aloca_pontos(size_t);
Ponto* proximo_ponto(Ponto*);
void le_ponto(Ponto*);
void imprime_ponto(void*);
bool compara_pontos(void*, void*);

#endif // PONTO_H
