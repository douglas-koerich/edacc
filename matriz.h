#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdlib.h>

// Definicao ABSTRATA do tipo "Matriz", cuja implementacao eh
// "invisivel" (encapsulada) para o programador-usuario
struct Matriz_;
typedef struct Matriz_ Matriz;

// Interface de operacoes da matriz, que fazem referencia ao tipo
// atraves de PONTEIROS (assim o compilador NAO PRECISA conhecer a
// estrutura interna)

/*
 * OPERACOES TIPICAS PARA UM TAD
 */

// Cria uma nova matriz com as dimensoes especificadas
Matriz* criar(size_t linhas, size_t colunas);

// Destroi uma matriz que foi criada anteriormente usando "criar"
void destruir(Matriz* matriz);

// Atribui um valor a uma das posicoes da matriz; retorna "falso" se
// a posicao eh invalida (fora dos limites)
// NOTA: a numeracao de linhas e colunas inicia em 1 (e nao em 0, como em C)
bool atribuir(Matriz* matriz, size_t linha, size_t coluna, double valor);

// Retorna o valor armazenado na posicao desejada; ocorre uma excecao
// de software (aborta o programa) se a posicao eh invalida
// (Repare o uso de "const" no ponteiro - impede alguma mudanca na matriz)
double consultar(const Matriz* matriz, size_t linha, size_t coluna);

// Imprime a matriz no console
void imprimir(const Matriz* matriz);

/*
 * OPERACOES ESPECIFICAS DE UMA MATRIZ, INDICADAS NO PROBLEMA
 */

// Soma duas matrizes e devolve uma nova matriz criada com o resultado; se
// as matrizes nao tiverem o mesmo tamanho, retorna um ponteiro nulo (NULL)
// NOTA: Deve-se destruir a matriz-resultado apos o seu uso
Matriz* soma(const Matriz* matriz_A, const Matriz* matriz_B);

// Multiplica a matriz por um escalar (numero), retornando uma outra matriz
// criada com o resultado
// (mesma NOTA anterior)
Matriz* produto_escalar(const Matriz* matriz, double fator);

// Multiplica duas matrizes e devolve uma nova matriz criada com o resultado;
// se as matrizes nao tiverem as dimensoes adequadas para a operacao (numero
// de colunas de A igual ao numero de linhas de B), retorna nulo (NULL)
// (mesma NOTA anterior)
Matriz* produto(const Matriz* matriz_A, const Matriz* matriz_B);

// Retorna a matriz transposta correspondente
// (mesma NOTA anterior)
Matriz* transposta(const Matriz* matriz);

#endif // MATRIZ_H