#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "listagen.h"

bool eh_vogal(char c) {
    switch (toupper(c)) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'Y':
            return true;
    }
    return false;
}

int main(void) {
    const char* palavra = "Diclorodifeniltricloretano";

    Lista* exemplo = cria();
    int i = 0;
    while (palavra[i] != '\0') {
        if (eh_vogal(palavra[i])) {
            ins_inicio(exemplo, palavra+i);
        } else {
            ins_fim(exemplo, &palavra[i]);
        }
        ++i;
    }
    puts("Lista ANTES das remocoes:");
    dump(exemplo);
    putchar('\n');

    char c;
    rem_fim(exemplo, &c);
    printf("Removido caractere '%c' do fim.\n", c);
    rem_inicio(exemplo, &c);
    printf("Removido caractere '%c' do inicio.\n", c);
    
    /*
    c = 'l'; // caractere a ser removido
    rem_valor(exemplo, &c);
    */

    puts("Lista DEPOIS das remocoes:");
    dump(exemplo);
    putchar('\n');

    destroi(exemplo);

    return EXIT_SUCCESS;
}

