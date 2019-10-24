#ifndef REGISTRO_H
#define REGISTRO_H

// Exemplo de um registro que faria parte de um banco de dados
struct Reg {
    unsigned chave; // campo que identifica um registro de forma unica
    char dado; // campo que ilustra os dados contidos num registro
    // (... outros campos viriam na sequencia ...)
};
typedef struct Reg Reg;

// Prototipo da operacao que troca o conteudo de dois registros
// entre si
void troca(Reg*, Reg*); // os dois enderecos dos registros

#endif // REGISTRO_H
