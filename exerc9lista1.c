#include "filaint_f.h"

void exerc9lista1(FilaInt* fila, int numero) {
    // Como nao sabe nada da implementacao da fila, nao adianta
    // criar um vetor para conter o que se tira da fila
    // (de qual tamanho seria ele???)
    // Entao, usa uma outra estrutura de dados auxiliar como
    // "passagem" dos valores
    FilaInt* auxiliar = cria_f();

    while (!underflow_f(fila)) {
        int num = dequeue_f(fila);

        // Soh passa para a auxiliar os valores maiores ou iguais
        // ao numero
        if (num >= numero) {
            enqueue_f(auxiliar, num);
        }
    }

    // Agora, devolve os numeros restantes para a fila original
    while (!underflow_f(auxiliar)) {
        enqueue_f(fila, dequeue_f(auxiliar));
    }

    // Antes de sair da funcao, tem que destruir a auxiliar!
    destroi_f(auxiliar);
}

