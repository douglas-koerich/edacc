#include <stdlib.h>
#include <limits.h>
#include "pilha.h" // definicao externa do TAD
#include "pilha_uso_interno.h" // definicao da estrutura interna

Pilha* cria(size_t tamanho) {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->vetor = malloc(sizeof(int)*tamanho);
    nova->topo = -1; // nao eh 0 pois 0 eh uma posicao valida, e nesse
                     // caso indicaria a existencia de um elemento na
                     // pilha
    nova->tamanho = tamanho; // para controle de ocupacao do vetor
                             // (v. funcao overflow)
    return nova; // retorna o endereco da estrutura recem-criada
}

void destroi(Pilha* pilha) {
    free(pilha->vetor);
    free(pilha);
}

// Uma funcao static soh eh visivel dentro da mesma unidade
// de compilacao (arquivo .c)
static bool overflow(const Pilha* pilha) {
    return pilha->topo == pilha->tamanho - 1;
}

bool underflow(const Pilha* pilha) {
    /*
    // retorna verdadeiro se pilha estah vazia
    if (pilha->topo == -1) {
        return true;
    } else {
        return false;
    }
    */
    return pilha->topo == -1;
}

void push(Pilha* pilha, int elemento) {
    if (overflow(pilha)) {
        return; // nao faz nada :-(
    }
    /*
    ++pilha->topo; // avanca para a proxima posicao (livre)
    pilha->vetor[pilha->topo] = elemento; // guarda nessa posicao
    */
    pilha->vetor[++pilha->topo] = elemento;
}

int pop(Pilha* pilha) {
    if (underflow(pilha)) {
        return INT_MIN; // retorna o extremo inferior da faixa de inteiros
    }
    /*
    int elemento = pilha->vetor[pilha->topo];
    --pilha->topo;
    return elemento;
    */
    return pilha->vetor[pilha->topo--]; // tem que decrementar DEPOIS
}

