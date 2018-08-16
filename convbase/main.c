#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

char* converte(int decimal, int base_destino);

int main(void) {
    printf("Digite um numero para converter: ");
    int numero;
    scanf("%d", &numero);

    int base;
    do {
        printf("Digite a base de destino (max. 16): ");
        scanf("%d", &base);
    } while (base < 2 || base > 16);

    char* string = converte(numero, base);
    printf("Numero convertido: %s\n", string);
    free(string); // assumindo que 'converte' criou uma string alocada dinamicamente

    return EXIT_SUCCESS;
}

char* converte(int decimal, int base_destino) {
    Pilha* auxiliar = cria();
    int quociente = decimal;
    while (quociente > 0) {
        int resto = quociente % base_destino;
        quociente /= base_destino; // para proxima iteracao do laco, se houver
        if (!overflow(auxiliar)) {
            push(auxiliar, resto);
        }
    }
    printf("Debug da pilha: ");
    imprime(auxiliar);
    putchar('\n');
    char* string = malloc(1024);
    int pos = 0;
    while (!underflow(auxiliar)) {
        char digito[2]; // espaco para um digito mais o \0 que o sprintf vai por
        sprintf(digito, "%hhx", pop(auxiliar)); // igual a printf, mas para string
        string[pos] = digito[0]; // o primeiro caractere da string eh o digito
        ++pos;
    }
    destroi(auxiliar);
    return string;
}

