#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdbool.h>	// tipo 'bool'
#include <stdlib.h>		// size_t

/*
 * Definicao do TAD: Dicionario
 * Lista linear de palavras (strings) ordenadas pela tabela ASCII
 */

// Declaracao da estrutura
struct Dicionario;	// eh o suficiente para compilar

// Interface de uso (operacoes)
struct Dicionario* cria(size_t max);							// max = previsao do maximo de palavras
void destroi(struct Dicionario* dic);							// remove o dicionario da memoria
bool insereInicio(struct Dicionario* dic, const char* palavra);	// retorna 'false' se nao pode inserir
bool insereFim(struct Dicionario* dic, const char* palavra);	// idem
bool insereOrdem(struct Dicionario* dic, const char* palavra);	// ibidem
bool removeInicio(struct Dicionario* dic);						// simplesmente remove, retorna 'false' se nao removeu
bool removeFim(struct Dicionario* dic);							// idem
bool removePalavra(struct Dicionario* dic, const char* palavra);// ibidem
bool busca(const struct Dicionario* dic, const char* palavra);	// retorna 'true' se a palavra estah na lista
void imprime(const struct Dicionario* dic);						// imprime a sequencia de palavras na ordem da lista

#endif	// DICIONARIO_H

