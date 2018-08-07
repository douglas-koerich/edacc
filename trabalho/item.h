#ifndef ITEM_H
#define ITEM_H

#include <time.h>

enum Tipo {
    ARQUIVO,
    DIRETORIO
};
typedef enum Tipo Tipo;

struct Lista;
struct Item {
    Tipo tipo;
    const char* nome;
    time_t tempo;
    union {
        struct {
            size_t tamanho;
        } arquivo;
        struct {
            struct Lista* conteudo;
        } diretorio;
    } detalhes;
};
typedef struct Item Item;

#endif
