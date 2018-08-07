#ifndef REGISTRO_H
#define REGISTRO_H

#include <string.h>

struct R {
    int chave;
    char qualquer_coisa;
};
typedef struct R R;

#define troca(r1, r2) ({ \
    R temp; \
    memcpy(&temp, &(r1), sizeof(R)); \
    memcpy(&(r1), &(r2), sizeof(R)); \
    memcpy(&(r2), &temp, sizeof(R)); \
})

#endif // REGISTRO_H
