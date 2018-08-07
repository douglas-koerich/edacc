#ifndef LISTAH_H
#define LISTAH_H

#include <stdbool.h>
#include "registro.h"

struct ListaReg;
typedef struct ListaReg ListaReg;

enum Extremo { INICIO, FIM };
typedef enum Extremo Extremo;

ListaReg* l_cria(void);
void l_destroi(ListaReg*);

bool l_underflow(const ListaReg*);

void l_insere(ListaReg*, Extremo, const Reg*);
void l_insere_ordem(ListaReg*, const Reg*);
void l_insere_posicao(ListaReg*, const Reg*, int);

/* Porque existe a funcao remove() na biblioteca-padrao da linguagem C,
 * vamos chamar as funcoes de remocao do TAD de exclui() */
Reg l_exclui(ListaReg*, Extremo);
Reg l_exclui_posicao(ListaReg*, int);
Reg l_exclui_chave(ListaReg*, const char*);

// Retorna o endereco do registro que contem a chave (NULL se nao existe)
const Reg* l_busca(const ListaReg*, const char*);

void l_imprime(const ListaReg*);

#endif
