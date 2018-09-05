#include <stdio.h>
#include "tipos.h"

// Codigo-fonte escrito pelo "usuario" implementando como se imprime
// o tipo de elemento que ele(a) quis armazenar na lista encadeada

void imprime_tipo(TipoChave x, const TipoReg* r) {
    printf("{%d,\"%s\"}", x, r->dado);
}

