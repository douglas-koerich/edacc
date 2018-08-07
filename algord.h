#ifndef _ALGORD_H_
#define _ALGORD_H_

/* Definicao de um registro-exemplo para uso na ilustracao dos algoritmos
   de ordenacao */
typedef struct {
    int chave_ordenacao;
    /* outros campos do registro vem na sequencia
       ... */
} Registro_Exemplo;

/* Prototipos das funcoes dos algoritmos */
void ordBolha(Registro_Exemplo vetor[], int n);
void ordSelecao(Registro_Exemplo vetor[], int n);
void ordInsercao(Registro_Exemplo vetor[], int n);
void ordShell(Registro_Exemplo vetor[], int n);
void ordRadix(Registro_Exemplo vetor[], int n);
void ordMerge(Registro_Exemplo vetor[], int esq, int dir);
void ordQuick(Registro_Exemplo vetor[], int esq, int dir);

#endif  /* _ALGORD_H_ */
