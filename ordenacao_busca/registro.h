#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdbool.h>

#define MAX 10

typedef struct Registro {
    unsigned chave;     // chave primaria (unica) do registro

    char campo_1[MAX];  // outros campos meramente ilustrativos
    float campo_2;
    bool campo_3;
} Registro;  // exemplo: registro simples

void preenche_registro_aleatorio(Registro*);
void imprime_registro(const Registro*);
void troca_registros(Registro*, Registro*);

#endif // REGISTRO_H

