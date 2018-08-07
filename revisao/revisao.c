/* Seja um deque de numeros inteiros. Escreva uma funcao que
 * "enxerte" um numero nesse deque de tal forma que a operacao,
 * uma vez realizada, faca com que todos os numeros menores que
 * o novo numero estejam a frente do mesmo, e todos os maiores
 * estejam apos o novo numero. As posicoes relativas dos menores
 * entre si e dos maiores entre si nao deve ser alterada.
 */

#include <stdlib.h>
#include <stdio.h>

/* Qualquer solucao para esse problema se inicia com a seguinte abordagem:
 * 1) O deque deve ser esvaziado pelo INICIO para avaliar os numeros presentes;
 * 2) Os numeros menores devem ser colocados em uma estrutura de dados auxiliar;
 * 3) Os numeros maiores devem ser colocados em outra estrutura auxiliar.
 *
 * Existem tres alternativas que poderiam ser utilizadas a partir dai:
 * a) Usando apenas filas para armazenar a ordem ORIGINAL dos numeros:
 * a.1) Tira-se da fila de menores inserindo no deque a partir do FIM do mesmo;
 * a.2) Adiciona-se o novo numero pelo FIM;
 * a.3) Tira-se da fila de maiores inserindo no deque, novamente pelo FIM.
 *
 * b) Usando apenas pilhas para armazenar os numeros, que ficarao INVERTIDOS:
 * b.1) Tira-se da pilha de maiores inserindo no deque a partir do INICIO;
 * b.2) Adiciona-se o novo numero pelo INICIO;
 * b.3) Tira-se da pilha de menores inserindo no deque pelo INICIO;
 *
 * c) Usando uma fila para os maiores, e uma pilha pelos menores;
 * c.1) Adiciona-se o novo numero ao deque vazio por qualquer lado;
 * c.2) Tira-se da pilha de menores inserindo no deque pelo INICIO;
 * c.3) Tira-se da fila de maiores inserindo no deque pelo FIM.
 *
 * Vamos apresentar aqui a alternativa (c).
 */
#include "deque.h"
#include "fila.h"
#include "pilha.h"

#define MAX_DEQUE   20
#define N           MAX_DEQUE-1

void enxerta(IDeque* d, int num);

int main(void) {
    IDeque* deque = d_cria(MAX_DEQUE);

    int i;
    for (i=0; i<N; ++i) {
        d_enqueue(deque, rand() % 100, i%2? INICIO: FIM);
    }
    printf("Estado inicial do deque: ");
    d_print(deque);

    int n;
    printf("\nDigite o numero que deve ser enxertado no deque: ");
    scanf("%d", &n);

    enxerta(deque, n);

    printf("Estado final do deque: ");
    d_print(deque);
    putchar('\n');

    d_destroi(deque);
    
    return EXIT_SUCCESS;
}

void enxerta(IDeque* d, int num) {
    IPilha* menores = p_cria(MAX_DEQUE);
    IFila* maiores = f_cria(MAX_DEQUE);

    while (!d_underflow(d)) {
        int n = d_dequeue(d, INICIO);
        if (n < num) {
            push(menores, n);
        }
        else {
            f_enqueue(maiores, n);
        }
    }
    d_enqueue(d, num, INICIO);
    while (!p_underflow(menores)) {
        d_enqueue(d, pop(menores), INICIO);
    }
    while (!f_underflow(maiores)) {
        d_enqueue(d, f_dequeue(maiores), FIM);
    }

    p_destroi(menores);
    f_destroi(maiores);
}

