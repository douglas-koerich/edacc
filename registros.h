#ifndef REGISTROS_H
#define REGISTROS_H

// DEFINICAO do modelo/registro / da estrutura (movida para registros.h)
// OBS.: Normalmente essa definicao fica a parte num arquivo-cabecalho
#define TAM_CAMPO_PLACA 8   // "ABC1234\0" - lembre-se do terminador-nulo!!!
#define TAM_CAMPO_MODELO 20
struct Carro {
    char placa[TAM_CAMPO_PLACA];
    char modelo[TAM_CAMPO_MODELO];
    char cor;   // 'M' ou 'F'
    int ano_fabricacao;
    // float potencia; // 1.0, 1.4, ...
};  // nao esquecer de terminar com ;
// Se eu nao quiser usar a palavra 'struct' toda vez que me referir a 'Carro',
// uso um typedef pra dar um apelido pra estrutura
typedef struct Carro carro; // poderia ser qualquer nome, inclusive "Carro"

#endif
