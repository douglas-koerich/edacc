#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bigint.h"
#include "pilha.h"

struct Digito {
    int digito;
    struct Digito* proximo;
};

struct BigInt {
    bool negativo;
    size_t num_digitos;
    struct Digito* menos_significativo;
};

static void verifica_numero(const BigInt* numero) {
    if (NULL == numero || NULL == numero->menos_significativo) {
        puts("ERRO: BigInt nulo");
        exit(EXIT_FAILURE);
    }
}

static void verifica_numeros(const BigInt* numero1, const BigInt* numero2) {
    if (NULL == numero1 || NULL == numero1->menos_significativo ||
        NULL == numero2 || NULL == numero2->menos_significativo) {
        puts("ERRO: BigInt nulo");
        exit(EXIT_FAILURE);
    }
}

static void remove_zeros_iniciais(BigInt* numero) {
    verifica_numero(numero);
    Pilha* p = cria();
    while (NULL != numero->menos_significativo) {
        struct Digito* digito = numero->menos_significativo;
        numero->menos_significativo = digito->proximo;
        --numero->num_digitos;
        push(p, digito->digito + '0');
        free(digito);
    }
    bool nao_zero = false;
    while (!underflow(p)) {
        int dig = pop(p) - '0';
        if (0 == dig && false == nao_zero) {
            continue;
        }
        nao_zero = true;
        struct Digito* digito = (struct Digito*) malloc(sizeof(struct Digito));
        digito->digito = dig;
        digito->proximo = numero->menos_significativo;
        numero->menos_significativo = digito;
        ++numero->num_digitos;
    }
    if (0 == numero->num_digitos) {
        struct Digito* digito = (struct Digito*) malloc(sizeof(struct Digito));
        digito->digito = 0;
        digito->proximo = numero->menos_significativo;
        numero->menos_significativo = digito;
        numero->negativo = false;
        ++numero->num_digitos;
    }
    destroi(p);
}

BigInt* aloca(const char* entrada) {
    BigInt* numero = (BigInt*) malloc(sizeof(BigInt));
    numero->menos_significativo = NULL;
    numero->num_digitos = strlen(entrada);
    numero->negativo = false;
    int i;
    for (i=0; i<strlen(entrada); ++i) {
        if (isdigit(entrada[i])) {
            struct Digito* novo = (struct Digito*) malloc(sizeof(struct Digito));
            novo->digito = entrada[i] - '0';
            novo->proximo = numero->menos_significativo;
            numero->menos_significativo = novo;
        } else if (0 == i) {
            --numero->num_digitos;
            if ('-' == entrada[i]) {
                numero->negativo = true;
            } else if ('+' == entrada[i]) {
                numero->negativo = false;
            } else {
                goto erro;
            }
        } else {
            goto erro;
        }
    }
    remove_zeros_iniciais(numero);
    return numero;
erro:
    desaloca(numero);
    return NULL;
}

void desaloca(BigInt* numero) {
    if (NULL == numero) {
        return;
    }
    while (NULL != numero->menos_significativo) {
        struct Digito* digito = numero->menos_significativo;
        numero->menos_significativo = digito->proximo;
        free(digito);
    }
    free(numero);
}

void imprime(const BigInt* numero) {
    if (NULL == numero || NULL == numero->menos_significativo) {
        printf("(nulo)");
        return;
    }
    if (true == numero->negativo) {
        putchar('-');
    }
    Pilha* p = cria();
    struct Digito* digito = numero->menos_significativo;
    int contador = 0;
    while (NULL != digito) {
        if (contador == 3) {
            push(p, '.');
            contador = 0;
        }
        push(p, digito->digito + '0');
        ++contador;
        digito = digito->proximo;
    }
    while (!underflow(p)) {
        putchar(pop(p));
    }
    destroi(p);
}

BigInt* copia(const BigInt* original) {
    if (NULL == original || NULL == original->menos_significativo) {
        return NULL;
    }
    BigInt* numero = (BigInt*) malloc(sizeof(BigInt));
    numero->menos_significativo = NULL;
    numero->num_digitos = original->num_digitos;
    numero->negativo = original->negativo;
    Pilha* p = cria();
    struct Digito* digito = original->menos_significativo;
    while (NULL != digito) {
        push(p, digito->digito + '0');
        digito = digito->proximo;
    }
    while (!underflow(p)) {
        digito = (struct Digito*) malloc(sizeof(struct Digito));
        digito->digito = pop(p) - '0';
        digito->proximo = numero->menos_significativo;
        numero->menos_significativo = digito;
    }
    destroi(p);
    return numero;
}

bool igual(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (numero1->negativo != numero2->negativo ||
        numero1->num_digitos != numero2->num_digitos) {
        return false;
    }
    struct Digito* digito1 = numero1->menos_significativo,
                 * digito2 = numero2->menos_significativo;
    while (NULL != digito1) {
        if (digito1->digito != digito2->digito) {
            return false;
        }
        digito1 = digito1->proximo;
        digito2 = digito2->proximo;
    }
    return true;
}

bool diferente(const BigInt* numero1, const BigInt* numero2) {
    return !igual(numero1, numero2);
}

bool menor(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (numero1->negativo != numero2->negativo) {
        return true == numero1->negativo;
    }
    if (numero1->num_digitos != numero2->num_digitos) {
        return numero1->num_digitos < numero2->num_digitos;
    }
    Pilha* p1 = cria();
    struct Digito* digito = numero1->menos_significativo;
    while (NULL != digito) {
        push(p1, digito->digito + '0');
        digito = digito->proximo;
    }
    Pilha* p2 = cria();
    digito = numero2->menos_significativo;
    while (NULL != digito) {
        push(p2, digito->digito + '0');
        digito = digito->proximo;
    }
    char eh_menor = '?';
    while (!underflow(p1)) {
        int digito1 = pop(p1) - '0';
        int digito2 = pop(p2) - '0';
        if (digito1 == digito2) {
            continue;
        }
        if (false == numero1->negativo && digito1 > digito2 ||
            true == numero1->negativo && digito1 < digito2) {
            eh_menor = 'n';
        } else {
            eh_menor = 'y';
        }
        break;
    }
    destroi(p1);
    destroi(p2);
    return 'y' == eh_menor;
}

bool maior(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (numero1->negativo != numero2->negativo) {
        return false == numero1->negativo;
    }
    if (numero1->num_digitos != numero2->num_digitos) {
        return numero1->num_digitos > numero2->num_digitos;
    }
    Pilha* p1 = cria();
    struct Digito* digito = numero1->menos_significativo;
    while (NULL != digito) {
        push(p1, digito->digito + '0');
        digito = digito->proximo;
    }
    Pilha* p2 = cria();
    digito = numero2->menos_significativo;
    while (NULL != digito) {
        push(p2, digito->digito + '0');
        digito = digito->proximo;
    }
    char eh_maior = '?';
    while (!underflow(p1)) {
        int digito1 = pop(p1) - '0';
        int digito2 = pop(p2) - '0';
        if (digito1 == digito2) {
            continue;
        }
        if (true == numero1->negativo && digito1 > digito2 ||
            false == numero1->negativo && digito1 < digito2) {
            eh_maior = 'n';
        } else {
            eh_maior = 'y';
        }
    }
    destroi(p1);
    destroi(p2);
    return 'y' == eh_maior;
}

bool menor_igual(const BigInt* numero1, const BigInt* numero2) {
    return igual(numero1, numero2) || menor(numero1, numero2);
}

bool maior_igual(const BigInt* numero1, const BigInt* numero2) {
    return igual(numero1, numero2) || maior(numero1, numero2);
}

void oposto(BigInt* numero) {
    verifica_numero(numero);
    numero->negativo = !numero->negativo;
}

BigInt* soma(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (numero1->negativo == numero2->negativo) {
        int s, vai_um = 0;
        Pilha* p = cria();
        struct Digito* parcela1 = numero1->menos_significativo,
                     * parcela2 = numero2->menos_significativo;
        while (NULL != parcela1 && NULL != parcela2) {
            s = parcela1->digito + parcela2->digito + vai_um;
            push(p, (s % 10) + '0');
            vai_um = s / 10;
            parcela1 = parcela1->proximo;
            parcela2 = parcela2->proximo;
        }
        while (NULL != parcela1) {
            s = parcela1->digito + vai_um;
            push(p, (s % 10) + '0');
            vai_um = s / 10;
            parcela1 = parcela1->proximo;
        }
        while (NULL != parcela2) {
            s = parcela2->digito + vai_um;
            push(p, (s % 10) + '0');
            vai_um = s / 10;
            parcela2 = parcela2->proximo;
        }
        if (0 != vai_um) {
            push(p, (vai_um % 10) + '0');
        }
        BigInt* sum = (BigInt*) malloc(sizeof(BigInt));
        sum->negativo = numero1->negativo;
        sum->num_digitos = 0;
        sum->menos_significativo = NULL;
        while (!underflow(p)) {
            struct Digito* digito = (struct Digito*) malloc(sizeof(struct Digito));
            digito->digito = pop(p) - '0';
            digito->proximo = sum->menos_significativo;
            sum->menos_significativo = digito;
            ++sum->num_digitos;
        }
        destroi(p);
        remove_zeros_iniciais(sum);
        return sum;
    } else {
        BigInt* sub;
        if (true == numero1->negativo) {
            BigInt* numero1_ = copia(numero1);
            oposto(numero1_);
            sub = subtrai(numero2, numero1_);
            desaloca(numero1_);
        } else {
            BigInt* numero2_ = copia(numero2);
            oposto(numero2_);
            sub = subtrai(numero1, numero2_);
            desaloca(numero2_);
        }
        return sub;
    }
}

void incrementa_de(BigInt* numero1, const BigInt* numero2) {
    BigInt* incrementado = soma(numero1, numero2);
    verifica_numero(incrementado);
    BigInt temp = *numero1;
    *numero1 = *incrementado;
    *incrementado = temp;
    desaloca(incrementado);
}

BigInt* subtrai(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (numero1->negativo == numero2->negativo) {
        BigInt* sub;
        if (true == numero1->negativo) {
            BigInt* numero1_ = copia(numero1);
            oposto(numero1_);
            BigInt* numero2_ = copia(numero2);
            oposto(numero2_);
            sub = subtrai(numero2_, numero1_);
            desaloca(numero1_);
            desaloca(numero2_);
            return sub;
        }
        sub = (BigInt*) malloc(sizeof(BigInt));
        sub->negativo = numero1->negativo;
        sub->num_digitos = 0;
        sub->menos_significativo = NULL;
        int s, vem_um = 0;
        struct Digito *minuendo, *subtraendo;
        if (maior_igual(numero1, numero2)) {
            minuendo = numero1->menos_significativo;
            subtraendo = numero2->menos_significativo;
        } else {
            minuendo = numero2->menos_significativo;
            subtraendo = numero1->menos_significativo;
            sub->negativo = !sub->negativo;
        }
        Pilha* p = cria();
        while (NULL != minuendo && NULL != subtraendo) {
            if (minuendo->digito < (subtraendo->digito + vem_um)) {
                s = 10 + minuendo->digito - (subtraendo->digito + vem_um);
                vem_um = 1;
            } else {
                s = minuendo->digito - (subtraendo->digito + vem_um);
                vem_um = 0;
            }
            push(p, s + '0');
            minuendo = minuendo->proximo;
            subtraendo = subtraendo->proximo;
        }
        while (NULL != minuendo) {
            if (minuendo->digito < vem_um) {
                s = 10 + minuendo->digito - vem_um;
                vem_um = 1;
            } else {
                s = minuendo->digito - vem_um;
                vem_um = 0;
            }
            push(p, s + '0');
            minuendo = minuendo->proximo;
        }
        while (!underflow(p)) {
            struct Digito* digito = (struct Digito*) malloc(sizeof(struct Digito));
            digito->digito = pop(p) - '0';
            digito->proximo = sub->menos_significativo;
            sub->menos_significativo = digito;
            ++sub->num_digitos;
        }
        destroi(p);
        remove_zeros_iniciais(sub);
        return sub;
    } else {
        BigInt* numero2_ = copia(numero2);
        oposto(numero2_);
        BigInt* sum = soma(numero1, numero2_);
        desaloca(numero2_);
        return sum;
    }
}

void decrementa_de(BigInt* numero1, const BigInt* numero2) {
    BigInt* decrementado = subtrai(numero1, numero2);
    verifica_numero(decrementado);
    BigInt temp = *numero1;
    *numero1 = *decrementado;
    *decrementado = temp;
    desaloca(decrementado);
}

BigInt* multiplica(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    const BigInt* num1 = numero1;
    BigInt* numero1_ = NULL;
    if (numero1->negativo) {
        numero1_ = copia(numero1);
        oposto(numero1_);
        num1 = numero1_;
    }
    const BigInt* num2 = numero2;
    BigInt* numero2_ = NULL;
    if (numero2->negativo) {
        numero2_ = copia(numero2);
        oposto(numero2_);
        num2 = numero2_;
    }
    BigInt* mul = aloca("0");
    BigInt* i = aloca("1");
    BigInt* um = aloca("1");
    while (true == menor_igual(i, num2)) {
        BigInt* multiplicado = soma(mul, num1);
        verifica_numero(multiplicado);
        BigInt temp = *mul;
        *mul = *multiplicado;
        *multiplicado = temp;
        desaloca(multiplicado);
        incrementa_de(i, um);
    }
    if (NULL != numero1_) {
        desaloca(numero1_);
    }
    if (NULL != numero2_) {
        desaloca(numero2_);
    }
    desaloca(i);
    desaloca(um);
    mul->negativo = numero1->negativo != numero2->negativo;
    return mul;
}

BigInt* potencia(const BigInt* numero1, const BigInt* numero2) {
    verifica_numeros(numero1, numero2);
    if (true == numero2->negativo) {
        puts("ERRO: expoente negativo");
        return NULL;
    }
    BigInt* pot = aloca("1");
    BigInt* i = aloca("1");
    BigInt* um = aloca("1");
    while (true == menor_igual(i, numero2)) {
        BigInt* elevado = multiplica(pot, numero1);
        verifica_numero(elevado);
        BigInt temp = *pot;
        *pot = *elevado;
        *elevado = temp;
        desaloca(elevado);
        incrementa_de(i, um);
    }
    desaloca(i);
    desaloca(um);
    return pot;
}
