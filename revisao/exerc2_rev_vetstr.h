#ifndef EXERC2_H
#define EXERC2_H

struct habitante {
    float salario;
    unsigned idade;
    unsigned filhos;
    char sexo;
};
typedef struct habitante habitante; // pode ser o mesmo nome

/* Definicao alternativa
 * typedef struct {
 *     float salario;
 *     unsigned idade, filhos;
 *     char sexo;
 * } habitante;
 */

#endif

