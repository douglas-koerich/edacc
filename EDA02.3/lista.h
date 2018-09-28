#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

struct Lista;
typedef struct Lista Lista;

Lista* cria(void);
void destroi(Lista*);
bool underflow(const Lista*);
bool overflow(const Lista*);
void imprime(const Lista*);
bool busca(const Lista*, const char*);

enum Posicao { INICIO, FIM, ORDEM, VALOR };
typedef enum Posicao Posicao;

void inserir(Lista*, const char*, Posicao);
void remover(Lista*, const char*, Posicao);

/**
 * NOVA OPERACAO SOLICITADA PELO EXERCICIO 3 DA LISTA
 * (PARTINDO DA PREMISSA QUE A LISTA NAO FOI CONSTRUIDA
 * EM ORDEM, I.E., NAO FOI CHAMADA inserir() COM POSICAO
 * IGUAL A 'ORDEM')
 */
void bubblesort_decrescente(Lista*);

#endif // LISTA_H

