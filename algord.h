#ifndef ALGORD_H
#define ALGORD_H

#include <stdlib.h>		// size_t
#include "registro.h"	// Para "conhecer" a estrutura do registro

// Prototipos das funcoes que implementam os diferentes algoritmos de ordenacao
void bubblesort(Registro[*], size_t);	// Bolha
void selectsort(Registro[*], size_t);	// Selecao direta
void insertsort(Registro[*], size_t);	// Insercao direta (ESTAVEL!)
void shellsort(Registro[*], size_t);	// Ordenacao de Shell (usando selecao)
void mergesort(Registro[*], int, int);	// Ordenacao por intercalacao (recursivo)
void quicksort(Registro[*], int, int);	// Ordenacao rapida (quicksort)
void radixsort(Registro[*], size_t);	// Ordenacao por "raiz"/digito (radixsort)

#endif	// ALGORD_H

