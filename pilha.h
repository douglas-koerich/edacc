#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

// Referencia a um tipo "opaco" que representa a Pilha
// na memoria do programa
struct Pilha;
typedef struct Pilha Pilha; // novo nome para o TAD

// Operacoes "classicas" do TAD Pilha
Pilha* cria(void); // uma nova pilha eh criada e seu endereco obtido
void destroi(Pilha*); // uma pilha passada como parametro eh destruida
bool underflow(const Pilha*); // testa se a pilha estah VAZIA (sem elementos)
bool push(Pilha*, char); // empilha um 'char' na pilha (true se havia espaco)
bool pop(Pilha*, char*); // desempilha para o ponteiro o 'char' do topo

// Operacoes extras que sejam de utilidade para a pilha
bool overflow(const Pilha*); // testa se a pilha estah cheia (por conveniencia)
#ifdef DEBUG // se esta constante estiver definida, 'imprime' eh conhecida
void imprime(const Pilha*); // imprime o conteudo da pilha (para depuracao)
#endif

#endif // PILHA_H

