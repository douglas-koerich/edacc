#ifndef BUSCA_H
#define BUSCA_H

struct Registro {
    int chave;      // chave de pesquisa (primaria)
    // ... outros campos do registro ...
};
typedef struct Registro Registro;

void quick(Registro*, int, int);
Registro* busca_sequencial(Registro*, size_t, int);
Registro* busca_binaria(Registro*, int, int, int);
Registro* busca_interpolacao(Registro*, int, int, int);

#endif  // BUSCA_H
