#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "generico2.h"

struct Lista;
typedef struct Lista Lista;

enum Extremidade { INICIO, FIM };
typedef enum Extremidade Extremidade;

Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
void insere(Lista*, Extremidade, const generico*);
void insere_ordem(Lista*, const generico*);   // apenas listas homogeneas
void insere_posicao(Lista*, unsigned, const generico*);
generico* exclui(Lista*, Extremidade);
generico* exclui_posicao(Lista*, unsigned);
generico* exclui_valor(Lista*, const generico*); // generico-in vazio, apenas com chave de busca
generico* busca(const Lista*, const generico*);  // idem
void imprime(const Lista*);

#endif
