#ifndef REGISTRO_H
#define REGISTRO_H

struct registro {
    int chave; // numero que identifica de forma unica este elemento
    char valor; // campo(s) associado(s) ah chave
    // ...
};
typedef struct registro Registro;

#endif // REGISTRO_H