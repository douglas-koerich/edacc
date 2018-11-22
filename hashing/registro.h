#ifndef REGISTRO_H
#define REGISTRO_H

// Registro-exemplo para um banco de dados armazenado numa
// tabela de hashing.
// IMPORTANTE: A funcao de hashing que vamos implementar no TAD
// implica que o registro deve usar uma chave alfanumerica

#define MAX_TAM_CHAVE 20
struct Reg {
    char chave[MAX_TAM_CHAVE];
    // campos ilustrativos
    int matricula;
    int codigo;
};
typedef struct Reg Reg;

#endif // REGISTRO_H

