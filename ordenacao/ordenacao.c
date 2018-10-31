#include <limits.h> // para saber a definicao de UINT_MAX (maior unsigned)
#include <math.h> // para uso do log10()
#include "ordenacao.h"
#include "fila.h" // necessario para radixsort()

void bolha(Registro vetor[], size_t tamanho) {
    int passagem;
    // Passagens no vetor para garantir que, no pior caso, todas as
    // chaves fiquem em suas posicoes finais
    for (passagem = 1; passagem <= tamanho-1; ++passagem) {
        int posicao;
        for (posicao = tamanho-1; posicao > 0; --posicao) {
            // Chave da posicao atual estah fora de ordem em relacao
            // a chave da posicao anterior (numa ordem crescente)?
            if (vetor[posicao].chave < vetor[posicao-1].chave) {
                // Troca os registros de posicao (contiguidade fisica)
                troca_registros(vetor + posicao, vetor + posicao - 1);
            }
        }
    }
}

void selecao(Registro vetor[], size_t tamanho) {
    int posicao = 0;
    while (posicao < tamanho-1) {
        // Busca a frente da posicao atual uma chave que seja menor do
        // que aquela armazenada aqui
        int pos, pos_menor = posicao; // comeca assumindo que a menor estah aqui
        for (pos = posicao+1; pos < tamanho; ++pos) {
            if (vetor[pos].chave < vetor[pos_menor].chave) {
                pos_menor = pos; // atualiza a posicao da menor chave
            }
        }
        troca_registros(vetor + posicao, vetor + pos_menor);
        ++posicao; // uma vez selecionado o menor para essa posicao, repete
                   // o processo para a posicao seguinte, ateh o fim do vetor
    }
}

void insercao(Registro vetor[], size_t tamanho) {
    int posicao = 1; // primeira posicao que pode ser comparada com o segmento
                     // anterior ("para tras") do vetor
    while (posicao < tamanho) {
        int pos_anterior = posicao - 1;
        Registro bkp = vetor[posicao]; // salva o registro da posicao inicial,
                                       // pois essa posicao pode ser sobrescrita
                                       // com o que vier da anterior
        while (pos_anterior >= 0 && vetor[pos_anterior].chave > bkp.chave) {
            vetor[pos_anterior+1] = vetor[pos_anterior]; // "empurra" o registro
                                                         // com maior chave pra frente
            --pos_anterior;
        }
        // Duas condicoes podem ter terminado o laco acima:
        // 1) pos_anterior = -1 (todas as posicoes comparadas tinham chaves maiores!)
        // 2) Chegou-se numa pos_anterior com chave menor ou igual a que eu tinha
        vetor[pos_anterior+1] = bkp; // insere o backup na posicao correta
        ++posicao;
    }
}

void radixsort(Registro vetor[], size_t tamanho) {
    // Como a chave do registro eh numerica, cria 10 filas para os 10
    // simbolos possiveis { 0, 1, ..., 9 }
    Fila* cjto_filas[10];
    int simb;
    for (simb=0; simb<=9; ++simb) {
        cjto_filas[simb] = cria();
    }

    int grandeza = 1; // inicia pelo LSD (digito menos significativo)
    const int MAX_GRANDEZA = log10(UINT_MAX) + 1; // quantos digitos tem o
                                                  // maior 'unsigned'
    while (grandeza <= MAX_GRANDEZA) {
        // Para todos os registros do vetor a ser ordenado...
        int i, d;
        for (i=0; i<tamanho; ++i) {
            // Descarta os digitos que estao ah direita da grandeza da vez
            unsigned chave = vetor[i].chave;
            for (d=1; d<grandeza; ++d) {
                chave /= 10;
            }
            // Recupera o digito da posicao relativa ah grandeza da vez
            int digito = chave % 10;

            // Poe o registro na fila correspondente ao digito
            enqueue(cjto_filas[digito], vetor+i);
        }
        i = 0; // retorna ao inicio do vetor de registros

        // Pra cada uma das filas ocupadas por chaves+registros de acordo
        // com o digito da grandeza da vez...
        for (d=0; d<=9; ++d) {
            // Esvazia a fila ...
            while (!underflow(cjto_filas[d])) {
                // ... para o vetor de registros
                const Registro* reg_na_fila = dequeue(cjto_filas[d]);
                vetor[i] = *reg_na_fila;
                ++i;
            }
        }
        ++grandeza; // digito mais significativo ah esquerda
    }

    // Antes de sair do algoritmo, destroi todas as filas
    for (simb=0; simb<=9; ++simb) {
        destroi(cjto_filas[simb]);
    }
}

