#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdbool.h>

struct Registro {
    int chave;  // identificacao univoca deste registro na base de dados
    char campo1; // informacao (dado) pertinente ao registro
    bool campo2; // outra informacao
    /* (...) */
};
typedef struct Registro Registro;

#endif
