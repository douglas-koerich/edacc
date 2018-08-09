#ifndef REV_PARTE1_H
#define REV_PARTE1_H

#define TAM_NOME_PAIS 50

// Item (a): definicao do registro

struct pais { // ATENCAO: NAO EH uma variavel, eh uma definicao de TIPO
    char nome[TAM_NOME_PAIS];   // 1.1 nome do pais
    int ativos;                 // 1.2 numero de ativos do pais
    int acidentes;              // 1.3 numero de acidentes do pais
    float perc_afastamento;     // 1.4 percentual de afastados (do pais)
};
typedef struct pais Pais; // 'Pais' eh apelido para o tipo 'struct pais'

// Item (d): declaracao (prototipo) da funcao
void melhor_pior_pais(Pais lista[*], int num_paises, // vetor de paises passado para a funcao
                      char nome_melhor[*], char* nome_pior, // vetores/ponteiros onde escrevera os nomes
                      int* num_acid_melhor, int* num_acid_pior); // enderecos onde escrevera os indices de acidentes

#endif
