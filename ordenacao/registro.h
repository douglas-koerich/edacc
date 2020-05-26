#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string.h>

struct R {
    unsigned chave; // campo usado como criterio da ordenacao/busca
    int valor; // apenas para ilustracao
};
typedef struct R R;

// r1 e r2 devem ser PONTEIROS nesta macro!!!
// Uso da estrategia de Contiguidade Fisica
#define TROCA(r1, r2) \
{ \
    R tmp; \
    memcpy(&tmp, (r1), sizeof(R)); \
    memcpy((r1), (r2), sizeof(R)); \
    memcpy((r2), &tmp, sizeof(R)); \
}

#endif // REGISTRO_H_
