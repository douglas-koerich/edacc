#ifndef REV8_H
#define REV8_H

#define TAM_SIGLA 2

// Definicao do tipo-registro correspondente as informacoes agregadas
// de um estado
struct info_estado {
    char sigla[TAM_SIGLA+1];    // reserva espaco adicional para o '\0'
    unsigned veiculos;
    unsigned acidentes;
};  // com ponto-e-virgula aqui!

// Apelido para o tipo info_estado
typedef struct info_estado Estado;

#endif

