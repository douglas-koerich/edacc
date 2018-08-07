#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(int argc, char* argv[]) {
    puts("*** Conversao decimal para outra base ***");
    unsigned base;
    do {
        printf("Digite a base desejada (2<=b<10): ");
        scanf("%u", &base);
    } while (base < 2 || base >= 10);
    unsigned decimal;
    printf("Digite o numero decimal: ");
    scanf("%u", &decimal);

    // Pilha como estrutura auxiliar
    // LEMBRETE: USAR ***APENAS*** A INTERFACE DO TAD!!!
    Pilha* aux = cria();    // "construtor"
    unsigned quociente = decimal;
    while (quociente > 0) {
        // Como a pilha armazena o endereco do elemento e nao o seu valor,
        // aloco na memoria um novo resto pois se usasse uma variavel local
        // a mesma seria destruida na proxima execucao do laco e o endereco
        // empilhado em "coisa" (do generico) ficaria invalido
        unsigned* resto = malloc(sizeof(unsigned));

        *resto = quociente % base;

        // Como nao vou usar a funcao de impressao da pilha, posso dar-me a
        // liberdade de nao definir (NULL) uma funcao de impressao da "coisa"
        generico resto_g = { resto, NULL };

        quociente = quociente / base;   // divide o numero para o proximo passo

        push(aux, &resto_g);
    }

    printf("O numero na base %u eh ", base);
    while (!underflow(aux)) {
        generico* p_resto = pop(aux);

        // O ponteiro que retorna no generico eh do tipo void*; com ele,
        // nao eh possivel usar o operador * (pegar o conteudo) da "coisa"
        // que foi empilhada; pra isso precisamos converter o ponteiro
        // usando cast (pra unsigned*)
        unsigned resto = *((unsigned*) p_resto->coisa);
        free(p_resto->coisa);   // no laco de cima, cada resto foi alocado
        free(p_resto);          // a funcao pop aloca um generico pra mim na
                                // hora de devolver, tirando da pilha
        printf("%u", resto);
    }
    printf(".\n");

    destroi(aux);           // "destrutor"

    return EXIT_FAILURE;
}

