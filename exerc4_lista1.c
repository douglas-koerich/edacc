#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pilhagen.h"

// Funcao que usa a interface do TAD 'Pilha' para remover o elemento
// contido na mesma, se houver
bool remove_elemento(Pilha*, const Tipo*);

int main(void) { // Programa de teste da funcao
    // Cria uma pilha de letras aleatorias
    printf("Quantos caracteres na pilha? ");
    size_t num;
    scanf("%zd", &num);

    char letra;
    srand((unsigned) time(NULL));

    Pilha* teste = cria(num);
    while (!overflow(teste)) {
        letra = rand() % ('Z'-'A' + 1) + 'A';
        printf("Empilhando letra '%c'...\n", letra);
        push(teste, &letra);
    }
    printf("Pilha de teste: ");
    dump(teste);
    putchar('\n');

    printf("Digite uma letra para ser removida da pilha: ");
    scanf(" %c", &letra);

    bool removeu = remove_elemento(teste, &letra);
    if (removeu) {
        printf("Removido, restou: ");
        dump(teste);
        putchar('\n');
    } else {
        puts("Nao encontrou letra na pilha!");
    }
    destroi(teste); // note que nao eh necessario esvaziar para destruir

    return EXIT_SUCCESS;
}

bool remove_elemento(Pilha* pilha, const Tipo* valor) {
    Pilha* aux = cria(1000); // isso faz pensar na importancia de fazer o exercicio 1...
    Tipo elemento;
    bool removeu = false;
    while (!underflow(pilha)) {
        pop(pilha, &elemento);
        if (memcmp(&elemento, valor, sizeof(Tipo)) == 0) { // elemento == *valor?
            removeu = true; // vai retornar com a sinalizacao de ter havido remocao
            continue; // despreza esse valor, pula para proxima iteracao do laco
        }
        push(aux, &elemento);
    }
    while (!underflow(aux)) {
        pop(aux, &elemento);
        push(pilha, &elemento);
    }
    destroi(aux);
    return removeu;
}

