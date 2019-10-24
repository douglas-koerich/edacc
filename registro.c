#include <stdlib.h>
#include <string.h>
#include "registro.h"

void troca(Reg* r1, Reg* r2) {
    Reg* aux = malloc(sizeof(Reg));
    memcpy(aux, r1, sizeof(Reg)); // *aux = *r1
    memcpy(r1, r2, sizeof(Reg));  // *r1 = *r2
    memcpy(r2, aux, sizeof(Reg)); // *r2 = *aux
    free(aux);
}

