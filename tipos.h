#ifndef TIPOS_H
#define TIPOS_H

#define MAX 10

typedef int TipoChave;  // exemplo: chave numerica
typedef struct Registro {
    char dado[MAX];
} TipoReg;  // exemplo: registro simples

void imprime_tipo(TipoChave, const TipoReg*);

#endif // TIPOS_H

