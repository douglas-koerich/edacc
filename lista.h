#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "tipos.h" // mais facil para o usuario reaproveitar o TAD 

// Definicao opaca do TAD: lista linear
struct Lista; // (pode ser encadeada ou nao)
typedef struct Lista Lista;

// Operacoes (interface) do TAD
Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
bool overflow(const Lista*);
void imprime(const Lista*);
TipoReg* busca(const Lista*, TipoChave);

enum Posicao { INICIO, // para inserir e remover
               FIM,    // idem
               ORDEM,  // para insercao em ordem
               VALOR   // para remocao de uma chave
};
typedef enum Posicao Posicao;

void inserir(Lista*, TipoChave, const TipoReg*, Posicao);
TipoReg remover(Lista*, TipoChave, Posicao);

#endif // LISTA_H

