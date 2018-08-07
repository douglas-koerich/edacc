#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "trabalho.h"

struct Lista* cria_arvore(const char* raiz) {
    DIR* dir = opendir(raiz);
    if (NULL == dir) {
        return NULL;
    }
    struct Lista* diretorio = NULL;
        item = cria();
        Item* novo = (Item*) malloc(sizeof(Item));
        novo->tipo = ARQUIVO;
        novo->nome = strdup(raiz);
        novo->tempo = ...;
        novo->detalhes.arquivo.tamanho = ...;
        return arq;
    }
    while (NULL != readdir(dir)) {

    }
}
