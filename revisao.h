#ifndef REVISAO_H
#define REVISAO_H

#include <stdlib.h>

// Definicao da estrutura
struct habitante {
    unsigned idade, num_filhos;
    char genero;
    float salario;
    // unsigned num_filhos;
};
typedef struct habitante pessoa;

// Declaracao das funcoes (prototipos)
void realiza_censo(pessoa [*], size_t);
float calcula_media(const pessoa*, size_t);
void encontra_maior_menor(const pessoa*, size_t, unsigned*, unsigned*);
unsigned conta_mulheres_3filhos_500reais(const struct habitante*, size_t);

#endif