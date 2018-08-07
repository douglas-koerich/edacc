#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ex6l6.h"

// Implementacao da tabela hashing usando tratamento de colisoes por encadeamento
// INTERIOR
// Status possiveis de uma entrada na tabela hashing
enum Status {
    LIVRE,      // nunca ocupada por nenhuma chave ou totalmente liberada
    OCUPADA,    // atualmente ocupada por uma chave
    VAZIA       // esta disponivel para uso por uma chave sinonima
};
typedef enum Status Status;

// A tabela hashing com tratamento de colisoes por encadeamento interior nao
// armazena apenas o registro, mas tambem informacoes que contam sobre essa
// entrada da tabela
struct EntradaTabela {
    Registro registro;
    int proximo;        // lista encadeada dentro do vetor ("interior")
    Status situacao;
};
typedef struct EntradaTabela EntradaTabela;

// Definicao do TAD: tabela hashing com encadeamento interior
struct TabelaHashing {
    EntradaTabela* vetor_originais;  // vetor das primeiras chaves,
                                     // inseridas antes de qualquer sinonima
    size_t tamanho_vetor_original;
    EntradaTabela* vetor_sinonimas;  // chaves que ja colidiram com as primeiras
    size_t tamanho_vetor_sinonimas;
    size_t contador_vetor_sinonimas; // controle de ocupacao do vetor adicional
    int primo;    // fator de divisao do metodo do resto na funcao de hashing
};

struct TabelaHashing* cria(size_t tamanho) {
    struct TabelaHashing* t = (struct TabelaHashing*) malloc(sizeof(struct TabelaHashing));
    t->vetor_originais = (EntradaTabela*) malloc(sizeof(EntradaTabela) * tamanho);
    t->tamanho_vetor_original = tamanho;

    // A escolha do tamanho do vetor de entradas sinonimas tem a ver com a
    // previsao do numero de registros que poderao ser de fato armazenados
    // Exemplo: considerar o mesmo tamanho como extra
    t->vetor_sinonimas = (EntradaTabela*) malloc(sizeof(EntradaTabela) * tamanho);
    t->tamanho_vetor_sinonimas = tamanho;

    // Deixa a tabela "limpa" para comecar a receber os registros...
    int i;
    for (i=0; i<t->tamanho_vetor_original; ++i) {
        t->vetor_originais[i].situacao = LIVRE;
        t->vetor_originais[i].proximo = -1;    // "lista vazia" (nao ha proximo)
    }
    for (i=0; i<t->tamanho_vetor_sinonimas; ++i) {
        t->vetor_sinonimas[i].situacao = LIVRE;
        t->vetor_sinonimas[i].proximo = -1;    // "lista vazia" (nao ha proximo)
    }
    t->contador_vetor_sinonimas = 0;

    // Calcula o primeiro primo maior que o tamanho definido, a ser usado na
    // funcao de hashing pra determinar a posicao de cada chave
    t->primo = tamanho+1;
    bool ehPrimo;
    do {
        ehPrimo = true;
        int divisor;
        for (divisor=t->primo-1; divisor>1; --divisor) {
            if (t->primo % divisor == 0) {
                ehPrimo = false;
                ++t->primo;
                break;
            }
        }
    } while (ehPrimo == false);

    return t;
}

void destroi(struct TabelaHashing* t) {
    free(t->vetor_sinonimas);
    free(t->vetor_originais);
    free(t);
}

static int funcao_hashing(const struct TabelaHashing* t, int chave) {
    int hash = chave % t->primo;  // metodo da divisao (ou do resto)
    if (hash >= t->tamanho_vetor_original) { // ja que primo eh maior que tamanho,
                                             // entao o resto pode passar do tamanho...
        hash -= t->tamanho_vetor_original;
    }
    return hash;
}

void insere(struct TabelaHashing* t, const Registro* r) {
    // Primeira posicao onde tentara guardar o registro eh a posicao no vetor de
    // originais indicada pela funcao de hashing
    int posicao = funcao_hashing(t, r->chave);

    // Toda insercao tenta verificar se a chave ja nao foi inserida antes; pra
    // isso, eh natural percorrer a "lista encadeada" com as chaves sinonimas
    // entre as quais pode estar a propria chave sendo inserida
    EntradaTabela* entrada = &t->vetor_originais[posicao]; // "cabeca" da lista
    EntradaTabela* vazia = NULL; // entrada da possivel tabela VAZIA que pode ser
                                 // usada por essa nova chave
    EntradaTabela* anterior = NULL; // como na lista encadeada convencional,
                                    // precisa lembrar do anterior para apontar
                                    // para o novo, quando inserir
    while (entrada->situacao != LIVRE) { // enquanto nao for lancado alem do fim
        if (entrada->situacao == OCUPADA &&
            entrada->registro.chave == r->chave) {
            // Chave ja existe na tabela, retorna sem inserir
            return;
        }
        if (entrada->situacao == VAZIA && vazia == NULL) {
            // Na primeira posicao vazia (liberada por outra sinonima) que
            // encontrar, marca ali o destino da nova chave
            vazia = entrada;    // vou inserir aqui (mas ainda preciso conferir
                                // se a chave nao existe mesmo nas proximas entradas)
        }
        // Se esta for a ultima sinonima...
        if (entrada->proximo == -1) {
            // Se encontrou uma entrada vazia antes, usa aquela entrada
            if (vazia != NULL) {
                entrada = vazia;
                break;
            }
            else {
                // Usa a proxima posicao livre do vetor de sinonimas
                if (t->contador_vetor_sinonimas == t->tamanho_vetor_sinonimas) {
                    // Nao ha mais espaco, nao insere a nova chave
                    return;
                }
                anterior = entrada;
                posicao = t->contador_vetor_sinonimas++;
                entrada = &t->vetor_sinonimas[posicao];
            }
        }
        else {
            anterior = entrada;
            posicao = entrada->proximo; // indice da proxima chave (sinonima) no
                                        // vetor adicional
            entrada = &t->vetor_sinonimas[posicao];
        }
    }
    // Adiciona a nova chave na tabela
    memcpy(&entrada->registro, r, sizeof(entrada->registro));
    entrada->situacao = OCUPADA;

    // Se existe uma entrada anterior, indica esta entrada como sua proxima
    if (anterior != NULL) {
        anterior->proximo = posicao;
    }
}

Registro* busca(struct TabelaHashing* t, int x) {
    // Primeira posicao onde vai procurar a chave eh aquela dada pela funcao de
    // hashing
    int posicao = funcao_hashing(t, x);
    EntradaTabela* entrada = &t->vetor_originais[posicao];

    // Laco para encontrar a chave nesta posicao ou nas proximas (sinonimas)
    while (entrada->situacao != LIVRE) {
        if (entrada->situacao == OCUPADA && entrada->registro.chave == x) {
            return &entrada->registro;
        }
        if (entrada->proximo == -1) {
            return NULL;
        }
        entrada = &t->vetor_sinonimas[entrada->proximo];
    }
    return NULL;
}

void imprime(const struct TabelaHashing* t) {
    const char* strStatus[] = { "LIVRE", "OCUPADA", "VAZIA" };
    puts("----- Conteudo da tabela hashing -----");
    puts("Ind Situacao Prox Chave");
    int i;
    puts("----- Chaves originais -----");
    EntradaTabela* entrada = t->vetor_originais;
    for (i=0; i<t->tamanho_vetor_original; ++i, ++entrada) {
        char chave[16] = "(nenhuma)";
        if (entrada->situacao == OCUPADA) {
            snprintf(chave, sizeof(chave), "%d", entrada->registro.chave);
        }
        printf("[%d] %8s %4d %s\n", i, strStatus[entrada->situacao],
               entrada->proximo, chave);
    }
    puts("----- Chaves sinonimas -----");
    entrada = t->vetor_sinonimas;
    for (i=0; i<t->tamanho_vetor_sinonimas; ++i, ++entrada) {
        char chave[16] = "(nenhuma)";
        if (entrada->situacao == OCUPADA) {
            snprintf(chave, sizeof(chave), "%d", entrada->registro.chave);
        }
        printf("[%d] %8s %4d %s\n", i, strStatus[entrada->situacao],
               entrada->proximo, chave);
    }
}
