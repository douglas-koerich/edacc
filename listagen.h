#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <stdbool.h> // definicao de bool para C
#include "tipo.h"    // tipo do elemento armazenado na lista

// Definicao OPACA (obscura) da implementacao da lista
typedef struct lista Lista;

// Interface de operacoes do TAD lista
Lista* cria(void); // a memoria (e o ceu) eh o limite
void destroi(Lista*);
void dump(const Lista*);
bool underflow(const Lista*); // testa se lista estah vazia
bool busca_valor(const Lista*, const Tipo*);
/* Essa implementacao de 'busca' eh apenas ilustrativa; na pratica,
 * ter-se-ia um REGISTRO armazenado no noh, e a busca pelo mesmo
 * seria feita por meio da sua CHAVE (um dos seus campos)
 * Exemplo:
 * Registro* busca(const Lista* lista_de_registros, const Tipo* chave);
 */
Tipo* busca_posicao(const Lista*, unsigned); // retorna o valor no n-esimo noh
void ins_inicio(Lista*, const Tipo*); // 'Tipo' eh o tipo do elemento armazenado
void ins_fim(Lista*, const Tipo*);
void ins_pos_fixa(Lista*, unsigned, const Tipo*);
void ins_pos_rand(Lista*, const Tipo*);
void ins_ordem_dir(Lista*, const Tipo*);
void ins_ordem_inv(Lista*, const Tipo*);
void rem_inicio(Lista*, Tipo*);
void rem_fim(Lista*, Tipo*);
void rem_pos_fixa(Lista*, unsigned, Tipo*);
void rem_pos_rand(Lista*, Tipo*);
void rem_valor(Lista*, const Tipo*);

#endif

