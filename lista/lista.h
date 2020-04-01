#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

// Definicao opaca do TAD: Lista
struct Lista;
typedef struct Lista Lista;

// Definicao do ponto de operacao dentro da lista
enum Posicao {
    CABECA, // no primeiro noh (inicio da lista)
    CAUDA,  // no ultimo noh (fim da lista)
    ORDEM,  // usado pela insercao quando se deve adicionar em ordem
    VALOR   // usado pela remocao quando buscando um valor especifico
};
typedef enum Posicao;

// Operacoes da interface do TAD
Lista* cria(void); // nao eh necessario informar o tamanho
void destroi(Lista* lista);
bool underflow(const Lista* lista); // banco de dados "vazio"
void insere(Lista* lista, int elemento, Posicao onde);
int retira(Lista* lista, Posicao onde, const int* valor); // ponteiro "valor"
    // eh usado somente quando "onde" contem VALOR

#endif // LISTA_H

