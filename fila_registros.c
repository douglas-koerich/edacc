#include <stdlib.h>
#include "fila_registros.h"
#include "lista.h"

struct fila {
    Lista* lista;
};

void f_enqueue(Fila* f, const Registro* r) {
    insert(f->lista, r, CAUDA, 0);
}

Registro* f_dequeue(Fila* f) {
    Registro* r = malloc(sizeof(Registro));
    extract(f->lista, r, CABECA, 0);
    return r;
}

bool f_underflow(const Fila* f) {
    return underflow(f->lista);
}

Fila* f_create(void) {
    Fila* f = malloc(sizeof(Fila));
    f->lista = create(); // cria lista encadeada
    return f;
}

void f_destroy(Fila* f) {
    destroy(f->lista);
    free(f);
}
