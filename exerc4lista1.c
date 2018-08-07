#include <stdbool.h>
#include "pilhaint_p.h"

bool exerc4lista1(PilhaInt* pilha, int numero) {
    // Como nao sabe nada da implementacao da pilha, nao adianta
    // criar um vetor pra conter o que se tira da pilha
    // (de qual tamanho seria ele???)
    // Entao, usa uma outra estrutura de dados auxiliar como
    // "passagem" dos valores
    PilhaInt* auxiliar = cria_p();

    bool achou = false; // variavel pra indicar se encontrou numero

    while (!underflow_p(pilha)) {
        int num = pop(pilha);

        // Soh passa para a auxiliar os valores diferentes do numero
        if (num != numero) {
            push(auxiliar, num);
        } else {
            achou = true;
        }
    }

    // Agora, a pilha auxiliar tem apenas os valores diferentes do
    // numero; deve retornar para a pilha original
    while (!underflow_p(auxiliar)) {
        push(pilha, pop(auxiliar)); // pop de uma, push na outra
    }

    // Antes de sair da funcao, tem que destruir a auxiliar!
    destroi_p(auxiliar);

    return achou;
}

