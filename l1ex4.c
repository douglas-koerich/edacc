#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Unico arquivo de referencia que permite usar a pilha
// como uma estrutura de dados (TAD)
#include "pilha.h"

bool remove_elemento(pilha* p, int x);

int main(void) {
    int exemplo[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, -1 };

    pilha* p = create(50);
    int i = 0;
    while (exemplo[i] != -1) {
        push(p, exemplo[i++]);
    }

    // Para depuracao apenas: imprime o conteudo da pilha para conferencia
    puts("A pilha...");
    print(p);

    int num;
    printf("\nDigite um numero para remover da pilha acima: ");
    scanf("%d", &num);

    if (remove_elemento(p, num) == true) {
        puts("Valor removido!");
        print(p);
        putchar('\n');
    } else {
        puts("Numero nao foi encontrado na pilha!");
    }

    destroy(p);

    return EXIT_SUCCESS;
}

bool remove_elemento(pilha* p, int x) {
    bool r = false;

    /* Uma pilha auxiliar eh a melhor escolha aqui pois:
    a) Nao eh necessario se preocupar em criar um vetor grande o suficiente
    para conter o numero da pilha;
    b) A devolucao dos elementos que forem tirados da pilha 'p' deve ser
    feita na ordem INVERSA da sequencia em que foram removidos, entao uma
    OUTRA pilha torna-se uma opcao natural */
    pilha* auxiliar = create(size(p));

    /* Pode ser que o valor 'x' ocorra mais de uma vez na pilha, entao eh
    necessario inspecionar a pilha 'p' inteira(o que soh eh possivel
    removendo os elementos) */
    while (underflow(p) == false) {
        int n = pop(p);
        if (n != x) {
            push(auxiliar, n);
        } else {
            r = true; // vai indicar que encontrou (e removeu)
        }
    }

    while (underflow(auxiliar) == false) {
        push(p, pop(auxiliar));
    }

    destroy(auxiliar);

    return r;
}