#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

/* Modificacao em relacao ao enunciado original:
 * Remove todos os _caracteres_ com codigo ASCII
 * menor que um determinado valor.
 */
void remove_menores(Fila*, char);

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Fila* f = cria();

    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        if (enqueue(f, exemplo[i])) {
            printf("Inserido o caractere %c\n", exemplo[i]);
        }
    }

#ifdef DEBUG
    printf("Fila ANTES"); imprime(f);
#endif

    char c;
    printf("Digite um caractere de referencia: ");
    scanf(" %c", &c);

    remove_menores(f, c);

#ifdef DEBUG
    printf("Fila DEPOIS"); imprime(f);
#endif

    destroi(f);

    return EXIT_SUCCESS;
}

void remove_menores(Fila* f, char ref) {
    Fila* apoio = cria();

    char c;
    while (!underflow(f)) {
        dequeue(f, &c);
        if (c >= ref) {
            enqueue(apoio, c);
        }
        // senao descarta...
    }
    while (!underflow(apoio)) {
        dequeue(apoio, &c);
        enqueue(f, c);
    }

    destroi(apoio);
}

