#include <stdlib.h>
#include <stdio.h>
#include "revisao.h"    // Para dar a conhecer a forma da estrutura no momento
                        // de declarar a variavel 'lista'

// Prototipos das funcoes
//void votacao(size_t num_votos, Candidato candidatos[], size_t num_candidatos);
int votacao(size_t num_votos, Candidato* candidatos, size_t num_candidatos);
int contagem(const Candidato* candidatos, size_t num_candidatos, int* max_votos);

#define ELEITORES   5

int main() {
    /* struct */ Candidato lista[] = {      // Ao inicializar um vetor com [] vazios,
        { 12, "Jaime Lerner", "PDT", 0 },   // o numero de elementos iniciais define
        { 13, "Dr. Rosinha", "PT", 0 },     // o tamanho desse vetor
        { 15, "Roberto Requiao", "PMDB", 0 },
        { 18, "Eliria Tim", "PH", 0 }
    };

    size_t tamanho_lista = sizeof(lista) / sizeof(Candidato);

    puts(">>> ELEICOES 1988 <<<");
    /*
    int v, nulos = 0;
    for (v=0; v<ELEITORES; ++v) {
        puts("Escolha o seu candidato (digite -1 para anular): ");
        int c;
        for (c=0; c<tamanho_lista; ++c) {
            printf("%d - %s\n", lista[c].numero, lista[c].nome);
        }
        printf("Voto? ");
        int voto;
        scanf("%d", &voto);
        if (voto == -1) {
            ++nulos;
        }
        for (c=0; c<tamanho_lista; ++c) {
            if (lista[c].numero == voto) {
                ++lista[c].votos;
                break;
            }
        }
    }
    */
    int nulos = votacao(ELEITORES, lista, tamanho_lista);
    /*
    int c, ganhador = 0, max_votos = lista[0].votos;
    for (c=0; c<tamanho_lista; ++c) {
        if (lista[c].votos > max_votos) {
            max_votos = lista[c].votos;
            ganhador = c;
        }
    }
    */
    int max_votos;
    // Como 'contagem' precisa devolver dois resultados (o ganhador e seu numero
    // de votos), preciso que um deles retorne por referencia, usando ponteiro
    int ganhador = contagem(lista, tamanho_lista, &max_votos);

    if (max_votos > nulos) {
        printf("O eleito eh %s.\n", lista[ganhador].nome);
    }
    else {
        puts("Eleicao anulada!");
    }
    return EXIT_SUCCESS;
}

int votacao(size_t num_votos, Candidato* candidatos, size_t num_candidatos) {
    int v, nulos = 0;
    for (v=0; v<num_votos; ++v) {
        puts("Escolha o seu candidato (digite -1 para anular): ");
        int c;
        for (c=0; c<num_candidatos; ++c) {
            printf("%d - %s\n", candidatos[c].numero, candidatos[c].nome);
        }
        printf("Voto? ");
        int voto;
        scanf("%d", &voto);
        if (voto == -1) {
            ++nulos;
        }
        Candidato* cursor = candidatos;
        for (c=0; c<num_candidatos; ++c, ++cursor) {
            if (cursor->numero == voto) {
                ++cursor->votos;
                break;
            }
        }
    }
    return nulos;
}

int contagem(const Candidato* candidatos, size_t num_candidatos, int* max_votos) {
    int c, ganhador = 0;
    //*max_votos = candidatos[0].votos;     // isso eh valido (indexacao de ponteiro)
    //*max_votos = *candidatos.votos;       // isso eh valido tambem (obtem primeiro o registro usando *)
    *max_votos = candidatos->votos;         // esse eh mais usado, partindo do endereco para o campo
    for (c=0; c<num_candidatos; ++c) {
        if (candidatos[c].votos > *max_votos) {
            //*max_votos = *(candidatos+c).votos;
            *max_votos = (candidatos+c)->votos;
            ganhador = c;
        }
    }
    return ganhador;
}
