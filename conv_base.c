#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhagen.h"
#include "dequegen.h" // usando como uma fila comum (insercao no FIM,
                      // remocao do INICIO)

void dec2bin(char*, size_t, int); // char* <-- int
void fdec2bin(char*, size_t, float); // char* <-- float

int main(void) {
    int i = 51;
    float f = 51.625F;
    char s[128];
    dec2bin(s, 32, i); // 32 por ser o numero maximo de bits de um inteiro
    printf("%d %o %x %s\n", i, i, i, s);
    fdec2bin(s, sizeof(s), f); // estabelece o tamanho da string como maximo
    printf("%f %s\n", f, s);
    return EXIT_SUCCESS;
}

void dec2bin(char* bin, size_t tam, int dec) {
    Pilha* aux = cria(tam);
    while (dec > 0) {
        int quoc = dec / 2;
        int resto = dec % 2;
        push(aux, &resto);
        dec = quoc; // para continuar o laco
    }
    // DEBUG: conteudo da pilha completa
    printf("Pilha: ");
    dump(aux);
    putchar('\n');

    // Construcao da string com os digitos binarios, caractere por caractere...
    int i = 0;
    while (!underflow(aux)) {
        int bit;
        pop(aux, &bit);
        bin[i] = bit + '0'; // conversao do inteiro para o ASCII correspondente
        ++i;
    }
    bin[i] = '\0'; // finaliza a string com o terminador nulo
    destroi(aux);
}

void fdec2bin(char* bin, size_t tam, float dec) {
    // O metodo de conversao separa as partes inteira e fracionaria do numero
    int inteira = dec;
    float frac = dec - inteira;

    dec2bin(bin, tam, inteira); // reusa o algoritmo de conversao baseado na pilha
    strcat(bin, ","); // acrescenta virgula ("Brasil,il,il!!") decimal
    if (frac == 0.0) { // se nao ha parte fracionaria no numero...
        strcat(bin, "0"); // ... nao haveria execucao do metodo da multiplicacao, e 
        return;           // portanto poe-se um '0' "forcado" apos a virgula
    }

    size_t max_frac = tam - strlen(bin);
    Deque* aux = cria_d(max_frac);

    // Metodo da multiplicacao para conversao da parte fracionaria
    while (frac != 0.0 && !overflow_d(aux)) {
        float prod = frac * 2;
        int inteira = prod; // esta variavel 'inteira' NAO EH a mesma da linha 48!
        enqueue_d(aux, &inteira, FIM); // usa o deque como FILA
        frac = prod - inteira;
    }
    // DEBUG: conteudo da fila completa
    printf("\"Fila\": ");
    dump_d(aux);
    putchar('\n');

    int i = strlen(bin); // inicia 'i' no indice atual do terminador nulo '\0'
    while (!underflow_d(aux)) {
        int bit;
        dequeue_d(aux, &bit, INICIO); // usa o deque como FILA
        bin[i] = bit + '0';
        ++i;
    }
    bin[i] = '\0'; // finaliza a string com o terminador nulo
    destroi_d(aux);
}
