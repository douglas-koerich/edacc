#ifndef _ALGBUSCA_H_
#define _ALGBUSCA_H_

/* Definicao de um registro-exemplo para uso na ilustracao dos algoritmos
   de ordenacao */
typedef struct {
    char chave;
    /* outros campos do registro vem na sequencia
       ... */
} Registro_Exemplo;

/* Prototipos das funcoes dos algoritmos */
int buscaSequencial(Registro_Exemplo vetor[], int n, char chaveBusca);
int buscaSentinela(Registro_Exemplo vetor[], int N, int* n, Registro_Exemplo* novo);
int buscaBinaria(Registro_Exemplo vetor[], int esq, int dir, char chaveBusca);
int buscaInterpolacao(Registro_Exemplo vetor[], int esq, int dir, char chaveBusca);

#endif	/* _ALGBUSCA_H_ */
