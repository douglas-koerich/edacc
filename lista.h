#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h> // size_t

struct Lista; // definicao opaca do tipo "Lista"
typedef struct Lista Lista;

enum Posicao {
    CABECA,      // para insercao (remocao) no (do) inicio da lista
    CAUDA,       // idem para o fim da lista
    CRESCENTE,   // para insercao em classificacao crescente dos elementos
    DECRESCENTE, // idem para classificacao decrescente
    FIXA         // para insercao (remoca) na (da) n-esima posicao da lista
};
typedef enum Posicao Posicao;

Lista* criar(void);
void destruir(Lista*);
void inserir(Lista*, char, Posicao, int);
bool remover(Lista*, char*, Posicao, int);
void remover_v(Lista*, char); // remover o elemento passado como parametro
bool underflow(const Lista*);
bool buscar(const Lista*, char); // verifica se elemento existe
                                 // (num caso mais pratico passaria um campo
                                 // e retornaria o endereco do registro que
                                 // o contem e que estah em um noh da lista)
size_t comprimento(const Lista*);

// NAO se tem a operacao overflow()!
#ifdef DEBUG
void imprimir(const Lista*);
#endif

// Operacoes relativas a exercicios da lista
bool comparar(const Lista*, const Lista*); // exercicio 2
void inverter(Lista*); // exercicio 8

#endif // LISTA_H

