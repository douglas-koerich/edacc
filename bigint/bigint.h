#ifndef BIGINT_H
#define BIGINT_H

#include <stdbool.h>

/* Definicao opaca do tipo numerico grande com sinal,
* implementado por lista encadeada. */
typedef struct BigInt BigInt;

/* Operacoes do tipo numerico grande com sinal, implementadas com
* auxilio da lista encadeada. */
BigInt* aloca(const char*);                         // Cria uma nova “variavel” desse tipo
                                                    // (a string contem a cadeia de numeros
                                                    // como foi lida do usuario)
void desaloca(BigInt*);                             // Libera a “variavel” da memoria
void imprime(const BigInt*);                        // Imprime o numero longo na tela
BigInt* copia(const BigInt*);                       // Operacao de atribuicao (copia)
bool igual(const BigInt*, const BigInt*);           // big1 == big2
bool diferente(const BigInt*, const BigInt*);       // big1 != big2
bool menor(const BigInt*, const BigInt*);           // big1 < big2
bool maior(const BigInt*, const BigInt*);           // big1 > big2
bool menor_igual(const BigInt*, const BigInt*);     // big1 <= big2
bool maior_igual(const BigInt*, const BigInt*);     // big1 >= big2
void oposto(BigInt*);                               // Inverte o sinal do proprio numero
BigInt* soma(const BigInt*, const BigInt*);         // big1 + big2
void incrementa_de(BigInt*, const BigInt*);         // big1 += big2
BigInt* subtrai(const BigInt*, const BigInt*);      // big1 - big2
void decrementa_de(BigInt*, const BigInt*);         // big1 -= big2
BigInt* multiplica(const BigInt*, const BigInt*);   // big1 * big2
BigInt* potencia(const BigInt*, const BigInt*);     // big1 ^ big2

#endif // BIGINT_H
