#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

// Definicao do registro armazenado na lista encadeada
struct Reg {
    int chave;  // Chave de busca
    int valor;  // Um exemplo de informacao associada a chave nesse registro
};
typedef struct Reg Reg;

// Definicao de um registro invalido
extern const Reg REG_INVALIDO;

// Definicao do TAD: Lista encadeada simples de registros do tipo Reg
struct Lista;

// Operacoes do TAD
struct Lista* cria(void);
void destroi(struct Lista* l);
bool underflow(const struct Lista* l);
void insereInicio(struct Lista* l, const Reg* novo);
void insereFim(struct Lista* l, const Reg* novo);
void insereOrdem(struct Lista* l, const Reg* novo);
Reg removeInicio(struct Lista* l);
Reg removeFim(struct Lista* l);
Reg removeRegistro(struct Lista* l, int chave_busca);
const Reg* busca(struct Lista* l, int chave_busca);
void imprime(struct Lista* l);
bool compara(const struct Lista* l1, const struct Lista* l2);

#endif
