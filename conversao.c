#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main() {
    int numero, base;
    long long convertido = 0;

    // Entrada de valores
    printf("Digite o numero a ser convertido: ");
    scanf("%d", &numero);
    do {
        printf("Digite a base de destino, de 2 a 9: ");
        scanf("%d", &base);
    } while (base < 2 || base > 9);

    // Uso de uma pilha para armazenar a sequencia de restos durante a conversao
    IPilha* p = cria(100);

    // Geracao dos restos pela divisao consecutiva do numero pela base
    int num = numero;
    while (num > 0) {
        int resto = num % base;
        if (!overflow(p)) {
            push(p, resto);
        }
        num /= base;
    }

    // Ao final do laco acima, a pilha tem a sequencia de restos, agora devemos
    // esvazia-la para obter o numero convertido
    while (!underflow(p)) {
        int resto = pop(p);
        convertido = convertido * 10 + resto;
    }

    // Destroi a pilha ao final de seu uso
    destroi(p);

    // Imprime o numero convertido
    printf("Numero na nova base: %lld\n", convertido);

    return EXIT_SUCCESS;
}
