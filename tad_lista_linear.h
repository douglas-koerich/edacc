#ifndef TAD_LISTA_LINEAR_H
#define TAD_LISTA_LINEAR_H

#include <stdbool.h>

#define MAX_NOME    20
struct Registro {
    int chave;
    char nome[MAX_NOME];
};
typedef struct Registro Registro;

struct ListaReg;
typedef struct ListaReg ListaReg;

ListaReg* criar(void);
void destruir(ListaReg* l);
bool underflow(const ListaReg* l);
// Nao ha operacao de overflow (nao existe limite no numero de nos/elementos)
void imprimir(const ListaReg* l);
Registro* buscar(const ListaReg* l, int x);
// Inserir novo primeiro item da lista
void inserir_cabeca(ListaReg* l, const Registro* r);
// Inserir novo ultimo item da lista
void inserir_cauda(ListaReg* l, const Registro* r);
// Inserir na ordem das chaves dos registros
void inserir_ordem(ListaReg* l, const Registro* r);
Registro remover_cabeca(ListaReg* l);
Registro remover_cauda(ListaReg* l);
Registro remover_chave(ListaReg* l, int x);

#endif
