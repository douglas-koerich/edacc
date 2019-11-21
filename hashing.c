#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include "hashing.h"
#include "lista_reg.h" // para o tratamento de colisoes (por encadeamento
                       // exterior, i.e., usando uma lista ligada)

struct Hash {
    Lista** vetor; // vetor de ponteiros ("ponteiro pra ponteiros")
                   // das listas encadeadas contendo as chaves sinonimas
    size_t m; // comprimento do vetor originalmente alocado
    unsigned M; // fator de ajuste para o tamanho na funcao de hashing
};

// Funcao auxiliar que calcula o maior numero primo maior que dado numero
static unsigned primo_maior(unsigned num) {
    bool eh_primo = false;
    unsigned teste = num;
    while (!eh_primo) {
        eh_primo = true;
        int inter;
        for (inter = 2; inter < teste; ++inter) {
            if (teste % inter == 0) {
                eh_primo = false;
                break;
            }
        }
        if (eh_primo == false) {
            ++teste;
        }
    }
    return teste;
}

Hash* h_criar(size_t num_total_posicoes) {
    Hash* h = malloc(sizeof(Hash));
    h->m = num_total_posicoes; // capacidade do vetor
    h->M = primo_maior(h->m);
    h->vetor = calloc(h->m, sizeof(Lista*)); // aloca vetor de ponteiros
    int i = 0;
    for (i = 0; i < h->m; ++i) {
        h->vetor[i] = criar(); // inicializa cada uma das listas encadeadas
    }
    return h;
}

void h_destruir(Hash* h) {
    if (h == NULL) {
        return;
    }
    int i = 0;
    for (i = 0; i < h->m; ++i) {
        destruir(h->vetor[i]); // destroi cada lista encadeada do vetor
    }
    free(h->vetor);
    free(h);
}

// Funcao de hashing utilizada para calcular a posicao com base
// no valor da chave
static int hashing(const Hash* h, unsigned chave) {
    if (h == NULL) {
        return -1;
    }
#if 1
    // Metodo da divisao
    int posicao = chave % h->M;
#else
    // Metodo pseudo-aleatorio
    // ATENCAO: nao usada neste exemplo porque a funcao main() definiu
    // uma semente para ser usada ao longo do programa na geracao
    // aleatoria de chaves de novos registros!!
    srand(chave); // chave eh a semente da sequencia pseudo-aleatoria
    int posicao = rand() % h->M;
#endif
    if (posicao >= h->m) { // se o resto eh maior que o ultimo indice...
        posicao -= h->m;
    }
#ifdef DEBUG
    printf("Para a chave %u foi definida a posicao %d\n", chave, posicao);
#endif
    return posicao;
}

void h_inserir(Hash* h, const Reg* r) {
    if (h == NULL) {
        return;
    }
    // Calcula a posicao onde serah armazenado o novo registro
    int posicao = hashing(h, r->chave);

    // Armazena o registro na lista encadeada correspondente do vetor
    inserir(h->vetor[posicao], r, CABECA, 0); // a rigor, deveriamos fazer
                                              // a insercao na lista
                                              // manualmente, e nao por TAD,
                                              // para verificar se a chave
                                              // jah nao estah na lista...
}

Reg* h_buscar(const Hash* h, unsigned chave) {
    if (h == NULL) {
        return NULL;
    }
    // Chama a mesma funcao que calculou a posicao de insercao
    // dessa chave (se existe) na tabela
    int posicao = hashing(h, chave);

    // Nao eh necessario percorrer o vetor, vamos diretamente ao indice
    // indicado pela funcao; porem, o registro pode nao estar (ainda) ali
    return buscar(h->vetor[posicao], chave); // usa funcao de busca da lista
}

void h_remover(Hash* h, unsigned chave) {
    if (h == NULL) {
       return;
    } 
    // Novamente, o valor da chave eh usado pra indicar qual eh a posicao
    // onde a mesma sera procurada (dessa vez, para remocao)
    int posicao = hashing(h, chave);
    remover_r(h->vetor[posicao], chave);
}

size_t h_tamanho(const Hash* h) {
    size_t soma_listas = 0;
    if (h != NULL) {
        int i;
        for (i = 0; i < h->m; ++i) {
            soma_listas += comprimento(h->vetor[i]); // soma o tamanho da lista
        }
    }
    return soma_listas;
}

void h_imprimir(const Hash* h) {
#ifdef DEBUG
    if (h == NULL) {
        printf("Hash invalido!");
        return;
    }
    int i;
    for (i = 0; i < h->m; ++i) {
        printf("[%d]: ", i);
        imprimir(h->vetor[i]);
    }
    putchar('\n');
#endif
}

