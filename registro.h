#ifndef REGISTRO_H
#define REGISTRO_H

struct registro {
    unsigned short chave;   // chave de busca do registro
    int valor;              // um valor qualquer ilustrativo do conteudo ("dado") do registro
};
typedef struct registro registro;

#endif  // REGISTRO_H
