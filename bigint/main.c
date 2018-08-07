#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "bigint.h"

#define INCR "1001"

char* gera_numero(size_t max) {
    size_t size = rand() % max + 1;
    char* num = (char*) calloc(size, sizeof(char));
    num[0] = rand() % 2? '-': '+';
    do {
        num[1] = rand() % 10 + '0';
    } while (num[1] == '0');
    int i; for (i=2; i<size-1; ++i) {
        num[i] = rand() % 10 + '0';
    }
    return num;
}

void libera_numero(char* num) {
    if (NULL == num) {
        free(num);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        goto error;
    }
    if (0 == strcmp(argv[1], "0") && argc < 4) {
        goto error;
    }
    srand((unsigned) time(NULL));
    size_t max = atoi(argv[1]);
    char *num1, *num2;
    if (0 == max) {
        num1 = argv[2];
        num2 = argv[3];
    } else {
        num1 = gera_numero(max);
        num2 = gera_numero(max);
    }
    BigInt* numero1 = aloca(num1);
    BigInt* numero2 = aloca(num2);
    BigInt* numero3 = copia(numero1);
    BigInt* numero4 = copia(numero1);

    oposto(numero4);

    printf("(aloca)  BigInt #1: "); imprime(numero1); putchar('\n');
    printf("(aloca)  BigInt #2: "); imprime(numero2); putchar('\n');
    printf("(copia)  BigInt #3: "); imprime(numero3); putchar('\n');
    printf("(oposto) BigInt #4: "); imprime(numero4); putchar('\n');

    printf("\n(igual) numero1 eh %s numero2\n",
           igual(numero1, numero2)? "IGUAL a": "DIFERENTE de");
    printf("(igual) numero1 eh %s numero3\n",
           igual(numero1, numero3)? "IGUAL a": "DIFERENTE de");
    printf("(igual) numero1 eh %s numero4\n",
           igual(numero1, numero4)? "IGUAL a": "DIFERENTE de");
    printf("(diferente) numero1 eh %s numero2\n",
           diferente(numero1, numero2)? "DIFERENTE de": "IGUAL a");
    printf("(diferente) numero1 eh %s numero3\n",
           diferente(numero1, numero3)? "DIFERENTE de": "IGUAL a");
    printf("(diferente) numero1 eh %s numero4\n",
           diferente(numero1, numero4)? "DIFERENTE de": "IGUAL a");

    printf("\n(menor) numero1 %s menor que numero2\n",
           menor(numero1, numero2)? "EH": "NAO EH");
    printf("(menor) numero1 %s menor que numero3\n",
           menor(numero1, numero3)? "EH": "NAO EH");
    printf("(menor) numero1 %s menor que numero4\n",
           menor(numero1, numero4)? "EH": "NAO EH");
    printf("(menor_igual) numero1 %s menor que ou igual a numero2\n",
           menor_igual(numero1, numero2)? "EH": "NAO EH");
    printf("(menor_igual) numero1 %s menor que ou igual a numero3\n",
           menor_igual(numero1, numero3)? "EH": "NAO EH");
    printf("(menor_igual) numero1 %s menor que ou igual a numero4\n",
           menor_igual(numero1, numero4)? "EH": "NAO EH");

    printf("\n(maior) numero1 %s maior que numero2\n",
           maior(numero1, numero2)? "EH": "NAO EH");
    printf("(maior) numero1 %s maior que numero3\n",
           maior(numero1, numero3)? "EH": "NAO EH");
    printf("(maior) numero1 %s maior que numero4\n",
           maior(numero1, numero4)? "EH": "NAO EH");
    printf("(maior_igual) numero1 %s maior que ou igual a numero2\n",
           maior_igual(numero1, numero2)? "EH": "NAO EH");
    printf("(maior_igual) numero1 %s maior que ou igual a numero3\n",
           maior_igual(numero1, numero3)? "EH": "NAO EH");
    printf("(maior_igual) numero1 %s maior que ou igual a numero4\n",
           maior_igual(numero1, numero4)? "EH": "NAO EH");

    BigInt* soma1 = soma(numero1, numero2);
    BigInt* soma2 = soma(numero1, numero4);
    BigInt* soma3 = soma(numero2, numero4);

    printf("\n(soma) #1 + #2: "); imprime(soma1); putchar('\n');
    printf("(soma) #1 + #4: "); imprime(soma2); putchar('\n');
    printf("(soma) #2 + #4: "); imprime(soma3); putchar('\n');

    desaloca(soma1);
    desaloca(soma2);
    desaloca(soma3);

    BigInt* numero1_ = copia(numero1);
    BigInt* numero2_ = copia(numero2);
    BigInt* numero4_ = copia(numero4);
    BigInt* incr = aloca(INCR);
    incrementa_de(numero1_, incr);
    incrementa_de(numero2_, incr);
    incrementa_de(numero4_, incr);

    printf("(incrementa_de) #1 += " INCR ": "); imprime(numero1_); putchar('\n');
    printf("(incrementa_de) #2 += " INCR ": "); imprime(numero2_); putchar('\n');
    printf("(incrementa_de) #4 += " INCR ": "); imprime(numero4_); putchar('\n');

    desaloca(numero1_);
    desaloca(numero2_);
    desaloca(numero4_);

    BigInt* sub1 = subtrai(numero1, numero2);
    BigInt* sub2 = subtrai(numero1, numero3);
    BigInt* sub3 = subtrai(numero1, numero4);

    printf("\n(subtrai) #1 - #2: "); imprime(sub1); putchar('\n');
    printf("(subtrai) #1 - #3: "); imprime(sub2); putchar('\n');
    printf("(subtrai) #1 - #4: "); imprime(sub3); putchar('\n');

    desaloca(sub1);
    desaloca(sub2);
    desaloca(sub3);

    numero1_ = copia(numero1);
    numero2_ = copia(numero2);
    numero4_ = copia(numero4);
    decrementa_de(numero1_, incr);
    decrementa_de(numero2_, incr);
    decrementa_de(numero4_, incr);

    printf("(decrementa_de) #1 -= " INCR ": "); imprime(numero1_); putchar('\n');
    printf("(decrementa_de) #2 -= " INCR ": "); imprime(numero2_); putchar('\n');
    printf("(decrementa_de) #4 -= " INCR ": "); imprime(numero4_); putchar('\n');

    desaloca(numero1_);
    desaloca(numero2_);
    desaloca(numero4_);
    desaloca(incr);

    printf("\n** Digite um fator de multiplicacao: ");
    long long int l_fator;
    scanf("%lld", &l_fator);
    char s_fator[24]; snprintf(s_fator, sizeof(s_fator), "%lld", l_fator);
    BigInt* fator = aloca(s_fator);
    BigInt* mul1 = multiplica(numero1, fator);
    BigInt* mul2 = multiplica(numero2, fator);
    BigInt* mul3 = multiplica(numero4, fator);

    printf("(multiplica) #1 * %s: ", s_fator); imprime(mul1); putchar('\n');
    printf("(multiplica) #2 * %s: ", s_fator); imprime(mul2); putchar('\n');
    printf("(multiplica) #4 * %s: ", s_fator); imprime(mul3); putchar('\n');

    desaloca(mul1);
    desaloca(mul2);
    desaloca(mul3);
    desaloca(fator);

    if (6 >= strlen(num1) && 6 >= strlen(num2)) {
        printf("\n^^ Digite um expoente de potencia: ");
        unsigned long long int u_fator;
        scanf("%llu", &u_fator);
        snprintf(s_fator, sizeof(s_fator), "%llu", u_fator);
        BigInt* expoente = aloca(s_fator);

        BigInt* pot1 = potencia(numero1, expoente);
        BigInt* pot2 = potencia(numero2, expoente);
        BigInt* pot3 = potencia(numero4, expoente);

        printf("(potencia) #1 ^ %s: ", s_fator); imprime(pot1); putchar('\n');
        printf("(potencia) #2 ^ %s: ", s_fator); imprime(pot2); putchar('\n');
        printf("(potencia) #4 ^ %s: ", s_fator); imprime(pot3); putchar('\n');

        desaloca(pot1);
        desaloca(pot2);
        desaloca(pot3);
        desaloca(expoente);
    } else {
        puts("\n^^ Numeros muito grandes para calculo da potencia, dispensado.\n");
    }

    desaloca(numero1);
    desaloca(numero2);
    desaloca(numero3);
    desaloca(numero4);

    if (0 != max) {
        libera_numero(num1);
        libera_numero(num2);
    }

    return EXIT_SUCCESS;
    
error:
    puts("Numero insuficiente de parametros na linha de comando");
    printf("Uso: %s <max-tam-num> [<num1> <num2>]\n", argv[0]);
    return EXIT_FAILURE;
}
