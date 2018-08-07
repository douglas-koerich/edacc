/**
 * TAD: Lista encadeada simples de numeros inteiros
 * Este arquivo-cabecalho apresenta a interface do TAD que pode ser
 * usada pelo programa-usuario da estrutura de dados "lista encadeada".
 * A implementacao (como eh formada/construida) e operada essa lista
 * eh oculta ao usuario.
 */

#ifndef LISTAE_H
#define LISTAE_H

// Definicao do tipo:
struct Lista;	// Isso eh suficiente para o compilador gerar o arquivo .o
				// do programa que USA o TAD (i.e. a lista)

// Posicoes tipicas de insercao na lista:
enum Posicao { INICIO, ORDEM, FIM };

// Interface do TAD (operacoes validas para esta lista linear):
struct Lista* criar(void);
int adicionar(struct Lista* l, int valor, enum Posicao pos);
int* buscar(struct Lista* l, int valor);
int remover(struct Lista* l, enum Posicao pos, int* valor);
int remover_val(struct Lista* l, int valor);
int remover_npos(struct Lista* l, unsigned npos, int* valor);
void imprimir(struct Lista* l);
void destruir(struct Lista* l);

#endif	// LISTAE_H

