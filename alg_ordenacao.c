#ifdef DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <math.h>
#include "registro.h"
#include "fila_reg.h" // apoio para o algoritmo radixsort()
#include "alg_ordenacao.h"

static void imprime_chaves(const Reg vetor[], size_t n) {
#ifdef DEBUG
    int i;
    for (i = 0; i < n; ++i) {
        printf("%u ", vetor[i].chave);
    }
    putchar('\n');
#endif
}

void bolha(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n); // imprime(?) as chaves no inicio
    int passagem;
    for (passagem = 1; passagem <= n; ++passagem) { // n passagens
        int posicao;
        for (posicao = n-1; posicao > 0; --posicao) {
            // Se existe uma chave menor na posicao mais a frente,
            // ela estah fora de ordem, deve trocar
            if (vetor[posicao].chave < vetor[posicao-1].chave) {
                troca(&vetor[posicao-1], &vetor[posicao]);
            }
        }
        // Imprime novamente as chaves apos essa passagem
        imprime_chaves(vetor, n);
    }
}

void selecao(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    int posicao;
    // Repete para todas as posicoes menos a ultima, que no final
    // acaba mesmo ficando com o maior valor
    for (posicao = 0; posicao < n-1; ++posicao) {
        int posicao_menor = posicao, outra_posicao;
        for (outra_posicao = posicao+1; outra_posicao < n; ++outra_posicao) {
            if (vetor[outra_posicao].chave < vetor[posicao_menor].chave) {
                posicao_menor = outra_posicao;
            }
        }
        // Usando aritmetica de ponteiros :-)
        troca(vetor + posicao, vetor + posicao_menor);
        imprime_chaves(vetor, n);
    }
}

void insercao(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    int posicao;
    // Comeca na segunda posicao do vetor pois a primeira nao
    // tem com quem ser comparada
    for (posicao = 1; posicao < n; ++posicao) {
        Reg* aux = malloc(sizeof(Reg));

        // Salva o registro original que vai ser reposicionado,
        // pois ele pode ser sobrescrito pelo deslocamento dos
        // outros
        memcpy(aux, vetor+posicao, sizeof(Reg));

        int posicao_anterior = posicao - 1;
        while (posicao_anterior >= 0 && // nao chegou no inicio E...
               vetor[posicao_anterior].chave > aux->chave) { // ... o anterior eh maior?
            memcpy(vetor+posicao_anterior+1, vetor+posicao_anterior,
                   sizeof(Reg)); // "empurra" o maior pra frente
            --posicao_anterior;
        }
        // Poe o elemento que estava sendo comparado na sua
        // posicao final
        memcpy(vetor+posicao_anterior+1, aux, sizeof(Reg));
        imprime_chaves(vetor, n);
    }
}

void shellsort(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    // Antes de iniciar a ordenacao, precisa da serie de incrementos
    // Gera enquanto k <= n (o seguinte seria o k > n)
    int serie_incrementos[32], i = 0, k = 1; // 1 eh o primeiro valor da serie
    while (k <= n) {
        serie_incrementos[i++] = k;
        k = 3 * k + 1; // formula de Shell
    }
    // Posiciona no primeiro incremento a ser considerado
    i -= 2;
    
    // Inicia o uso dos incrementos em valores decrescentes
    int incremento;
    while (i >= 0) {
        incremento = serie_incrementos[i];

        // O vetor eh dividido em "segmentos virtuais", formados pelos elementos
        // salteados de incremento em incremento; o numero de segmentos eh igual ao valor do incremento da vez :-)
        int segmento, segmentos = incremento;
        for (segmento = 0; segmento < incremento; ++segmento) {
            // Compare com o algoritmo de selecao direta (original); onde se
            // percorria o vetor de 1 em 1, percorre-se de incremento em incremento
            int posicao;
            for (posicao = segmento; posicao < n; posicao += incremento) {
                int posicao_menor = posicao, outra_posicao;
                for (outra_posicao = posicao+incremento; outra_posicao < n; outra_posicao += incremento) {
                    if (vetor[outra_posicao].chave < vetor[posicao_menor].chave) {
                        posicao_menor = outra_posicao;
                    }
                }
                // Usando aritmetica de ponteiros :-)
                troca(vetor + posicao, vetor + posicao_menor);
            }
        }
#ifdef DEBUG
        printf("k = %d\n", incremento);
#endif
        imprime_chaves(vetor, n);
        --i; // Vai para o incremento menor, repetindo a divisao em segmento(s)
    }
}

void radixsort(Reg vetor[], size_t n) {
    int digito;
    Fila* filas_digitos[10];
    for (digito = 0; digito < 10; ++digito) {
        filas_digitos[digito] = cria(); // cria filas para cada digito 0-9
        imprime(filas_digitos[digito]);
    }
    const int POT10_MAX = 9; // como a chave eh do tipo unsigned, o maior
                             // valor a ser considerado eh na casa do
                             // bilhao (10^9)
    int pot10 = 0;
    imprime_chaves(vetor, n);
    while (pot10 <= POT10_MAX) {
        int posicao, grandeza = pow(10, pot10); // unidade, dezena, centena...
        for (posicao = 0; posicao < n; ++posicao) {
            unsigned chave = vetor[posicao].chave;
            if (grandeza > 1) {
                chave /= grandeza; // retira os digitos ah direita
                                   // da posicao do digito desejado
            }
            // O digito procurado estah agora na posicao mais ah direita
            // do numero
            digito = chave % 10;

            // Copia para a fila CORRESPONDENTE ao digito da chave o
            // registro armazenado no vetor
            enqueue(filas_digitos[digito], vetor+posicao);
        }
        posicao = 0; // retorna ao inicio do vetor
        for (digito = 0; digito < 10; ++digito) {
            imprime(filas_digitos[digito]);
            while (!underflow(filas_digitos[digito])) { // esvazia a fila
                dequeue(filas_digitos[digito], vetor+posicao);
                ++posicao;
            }
        }
        imprime_chaves(vetor, n);
        ++pot10; // para continuar na posicao do digito ah esquerda
    }
    for (digito = 0; digito < 10; ++digito) {
        destroi(filas_digitos[digito]);
    }
}

