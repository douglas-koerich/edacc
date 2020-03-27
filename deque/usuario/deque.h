#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdbool.h>
#include <stdlib.h>

// Definicao do "lado" valido para as operacoes de insercao/remocao no
// deque
enum Lado {
    INICIO, // para insercoes e remocoes no inicio do deque
    FIM     // idem, para o fim do deque
};
typedef enum Lado Lado;

// Toda definicao de TAD eh feita de maneira "oculta" para o usuario
// do mesmo
struct Deque; // declaracao opaca da estrutura
typedef struct Deque Deque;

// Seguem os prototipos das funcoes, isto eh, as operacoes definidas
// na interface do TAD
Deque* cria(size_t tamanho); // cria um nova deque e retorna seu endereco
void destroi(Deque* deque);
void insere(Deque* deque, int elemento, Lado onde); // insere um novo elemento no fim
int retira(Deque* deque, Lado onde); // remove o elemento do inicio
bool underflow(const Deque* deque); // funcao de teste nao altera conteudo

#endif // DEQUE_H_

