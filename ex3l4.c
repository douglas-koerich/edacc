#include <stdlib.h>
#include <stdio.h>

#define MAX_STRING  20

int contaCaracter(const char*, char);

int main(void) {
    char string[MAX_STRING];

    printf("Digite uma palavra ou frase bem curta: ");
    gets(string);
    printf("Qual caracter espera encontrar nessa string? ");
    char ch;
    scanf(" %c", &ch);

    int cont = contaCaracter(string, ch);
    printf("O caracter apareceu %d vezes.\n", cont);

    return EXIT_SUCCESS;
}

int contaCaracter(const char* posicao_string, char caracter) {
    // Condicao terminal, nao ha o que procurar alem desta posicao...
    if (*posicao_string == '\0') {
        return 0;   // terminador nulo <> caracter procurado
    }
    else {
        int contador = (*posicao_string == caracter)? 1: 0;

        // Fase ativa: precisa chamar o mesmo algoritmo para
        // contabilizar o restante da string
        contador += contaCaracter(posicao_string+1, caracter);
        return contador;
    }
}

