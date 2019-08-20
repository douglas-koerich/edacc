/* Aplicacao de pilha:
 * Conversao de um numero decimal lido do teclado
 * para uma string alfanumerica que corresponde ao numero
 * em uma base entre 2 ({0,1}) e 37 ({0,1,2,...,X,Y,Z}) */

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h" // para conhecer o TAD Pilha e suas operacoes

size_t conv_dec_para_baseN( // retorna o numero real de algarismos convertidos
    unsigned numero,    // numero decimal a ser convertido
    char* string,       // string que conterah a representacao na base N
    size_t max_tamanho, // capacidade da string passada como parametro
    unsigned base);     // base numerica de destino da conversao (2 a 37)

int main(void) {
    printf("Digite um numero na base decimal: ");
    unsigned n;
    scanf("%u", &n);

    unsigned b;
    do {
        printf("Qual a base de destino (2-37)? ");
        scanf("%u", &b);
    } while (b < 2 || b > 37);

    size_t tamanho;
    printf("Quantos algarismos reservar para a conversao? ");
    scanf("%zd", &tamanho);

    char convertido[tamanho];
    size_t num_real_algarismos;
    num_real_algarismos = conv_dec_para_baseN(n, convertido, tamanho, b);

    printf("A representacao do numero %u na base %u eh %s\n", n, b, convertido);
    if (num_real_algarismos > tamanho) {
        printf("ALERTA: o numero convertido tem %zd algarismos,\n"
               "acima da capacidade da string!\n", num_real_algarismos);
    }

    return EXIT_SUCCESS;
}

size_t conv_dec_para_baseN(unsigned numero, char* string, size_t max_tamanho,
                           unsigned base) {
    Pilha* restos = cria();
    unsigned quociente = numero;
    size_t contador_algarismos = 0;
    while (quociente > 0) {
        unsigned resto = quociente % base;
        quociente /= base;

        char r;
        if (resto < 10) {
            r = resto + '0';        // converte para ASCII o algarismo numerico
        } else {
            r = resto - 10 + 'A';   // converte para ASCII o algarismo alfabetico
        }
        push(restos, r); // empilha o caractere correspondente ao resto na base
        ++contador_algarismos;
    }
    int i = 0;
    while (!underflow(restos) && i < max_tamanho-1) { // reserva para o '\0'
        pop(restos, string+i); // 'popa' para o endereco string+i (=&string[i])
        ++i;
    }
    string[i] = '\0'; // "fecha" a string do numero convertido

    destroi(restos);

    return contador_algarismos;
}

