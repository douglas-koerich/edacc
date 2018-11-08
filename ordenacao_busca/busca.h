#ifndef BUSCA_H
#define BUSCA_H

#include <stdlib.h>
#include "registro.h"

extern unsigned comparacoes;

// Todos os algoritmos retornam a posicao no vetor onde foi encontrada a chave
// ou -1 se ela nao existe no vetor
int sequencial(Registro [*], size_t, unsigned); // ultimo parametro eh a chave
int binaria(Registro [*], int, int, unsigned);
int interpolacao(Registro [*], int, int, unsigned);

#endif // BUSCA_H

