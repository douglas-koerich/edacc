#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "filagen.h"

// Funcao que usa a interface do TAD 'Fila' para remover o elemento
// contido na mesma, se houver
bool remove_menores(Fila*, const Tipo*);

int main(void) { // Programa de teste da funcao
    // Cria uma fila de numeros aleatorios
    printf("Quantos numeros na fila? ");
    size_t num;
    scanf("%zd", &num);

    int numero;
    srand((unsigned) time(NULL));

    Fila* teste = cria(num);
    while (!overflow(teste)) {
        numero = rand() % 100;
        printf("Enfileirando numero %d...\n", numero);
        enqueue(teste, &numero);
    }
    printf("Fila de teste: ");
    dump(teste);
    putchar('\n');

    printf("Digite um numero de referencia para remocao dos menores da fila: ");
    scanf("%d", &numero);

    bool removeu = remove_menores(teste, &numero);
    if (removeu) {
        printf("Removido(s), restou: ");
        dump(teste);
        putchar('\n');
    } else {
        puts("Soh encontrou Maiores na fila!");
    }
    destroi(teste); // note que nao eh necessario esvaziar para destruir

    return EXIT_SUCCESS;
}

bool remove_menores(Fila* fila, const Tipo* referencia) {
    Fila* aux = cria(1000); // isso faz pensar na importancia de fazer o exercicio 6...
    Tipo elemento;
    bool removeu = false;
    while (!underflow(fila)) {
        dequeue(fila, &elemento);
        if (elemento < *referencia) {
            removeu = true; // vai retornar com a sinalizacao de ter havido remocao
            continue; // despreza esse valor, pula para proxima iteracao do laco
        }
        enqueue(aux, &elemento);
    }
    while (!underflow(aux)) {
        dequeue(aux, &elemento);
        enqueue(fila, &elemento);
    }
    destroi(aux);
    return removeu;
}

