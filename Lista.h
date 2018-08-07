/**
 * TAD: Lista linear de numeros inteiros
 * Este arquivo-cabecalho apresenta a interface do TAD que pode ser
 * usada pelo programa-usuario da estrutura de dados "lista linear".
 * A implementacao (como eh formada/construida) e operada essa lista
 * eh oculta ao usuario.
 */

#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>	// para definicao do size_t

// Definicao do tipo:
struct Lista;	// Isso eh suficiente para o compilador gerar o arquivo .o
				// do programa que USA o TAD (i.e. a lista)

// Posicoes tipicas de insercao na lista:
enum Posicao { INICIO, ORDEM, FIM };

// Interface do TAD (operacoes validas para esta lista linear):
struct Lista* criar(size_t max);
int adicionar(struct Lista* l, int valor, enum Posicao pos);
int buscar(struct Lista* l, int valor);
int remover(struct Lista* l, int valor);
void imprimir(struct Lista* l);
void ordenar(struct Lista* l);
void destruir(struct Lista* l);

#endif	// LISTA_H

