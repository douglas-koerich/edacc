/* Laboratorio de aplicacao de hashing e seus conceitos:
 * Problema: "Um sistema mantem uma tabela de senhas de usuarios, alfanumericas
 * de comprimento maximo de 8 caracteres quaisquer entre minusculas, maiusculas
 * (nao acentuadas), algarismos (de 0 a 9) e o sublinhado (_). Nesta tabela, a
 * senha eh associada a outras caracteristicas do usuario dono da senha."
 *
 * Escreva um programa em C que armazene essas senhas em uma tabela hashing com
 * ate 1000 posicoes, pois sabe-se que ha, em media, 700 usuarios cadastrados no
 * sistema. Seu programa deve simular o cadastramento inicial de senhas (conteu-
 * do e comprimentos aleatorios) nessa tabela, para um numero de 500 usuarios.
 * Escreva o codigo-fonte da(s) funcao(oes) para:
 * > determinar a posicao (hashing) da tabela onde a senha sera armazenada;
 * > fazer o tratamento de colisoes entre chaves, usando a estrategia de espa-
     lhamento sequencial;
 * > buscar uma senha na tabela (simule a pesquisa usando senhas aleatorias).
 *
 * Sugere-se, para aumentar sua compreensao do assunto, escrever codigo adicio-
 * nal para:
 * > contabilizar o numero de chaves que colidiram para cada posicao (confirman-
 *   do assim se a funcao de hashing escolhida faz a distribuicao *uniforme*);
 * > mudar para outra funcao de hashing e reavaliar o resultado da distribuicao;
 * > mudar a estrategia de tratamento de colisoes para encadeamento (com lista
 *   encadeada) e/ou espalhamento duplo (uso de uma segunda funcao de hashing
 *   para encontrar outra posicao para a chave que colidiu com a existente). */

#ifndef _LABHASHING_H_
#define _LABHASHING_H_

/*
 * Definicao: MAX_STRING - comprimento maximo da string (caracteres validos).
 */
#define MAX_STRING	8

/*
 * Definicao: TAM_TABELA - numero de posicoes da tabela de senhas.
 */
#define TAM_TABELA	1000

/*
 * Definicoes: estado da posicao no vetor, usado para insercao e principalmente
 * para busca.
 */
typedef enum Estado {
	POSICAO_LIVRE,		/* esta posicao nunca foi ocupada por uma senha */
	POSICAO_OCUPADA,	/* esta posicao contem uma senha no momento */
	POSICAO_LIBERADA	/* esta posicao foi liberada mas existe outra a frente */
} Estado;

/*
 * Definicao: cada uma das posicoes da tabela hashing eh da seguinte forma:
 */
typedef struct Item {
	Estado estado;				/* este item eh livre, ocupado ou liberado */
	char senha[MAX_STRING+1];	/* a senha armazenada nesta posicao da tabela */
	/*... outras informacoes do registro estariam armazenadas aqui tambem... */
} Item;

/*
 * Funcao: hashSenha()
 * Sumario: Obtem um numero (hash) no intervalo de 0 a 999 (posicoes validas na
 *          tabela) a partir do valor da senha.
 * Parametro: senha - string contendo a senha da qual se obtera o hash.
 * Retorno: O numero da posicao na tabela.
 */
int hashSenha(const char* senha);

/*
 * Funcao: espalhaSequencial()
 * Sumario: Encontra uma nova posicao a frente no vetor para uma chave que coli-
 *          diu com outra que ja existia na posicao original determinada pela
 *          funcao de hash.
 * Parametro: tabela - a tabela que sera percorrida a procura da posicao.
 * Parametro: posOriginal - indice da posicao original no vetor, onde colidiu.
 * Retorno: Posicao onde devera ser armazenada a chave que colidiu, ou -1 se o
 *          vetor ja esta cheio.
 */
int espalhaSequencial(Item* tabela, int posicaoOriginal);

/*
 * Funcao: inserir()
 * Sumario: Usando as funcoes acima, determina a posicao de uma nova senha na
 *          tabela (original ou espalhada devido a colisao) e insere o registro
 * Parametro: tabela - a tabela onde se quer inserir a nova senha
 * Parametro: senha - string contendo a senha que sera inserida.
 * Retorno: Valor booleano - resultado da insercao com sucesso ou insucesso.
 */
int inserir(Item* tabela, const char* senha);

/*
 * Funcao: buscar()
 * Sumario: Retorna a posicao real do vetor onde se encontra a chave, mesmo que
 *          ela tenha colidido com outra quando da sua insercao.
 * Parametro: tabela - a tabela que sera percorrida a procura da senha.
 * Parametro: senha - string contendo a senha procurada na tabela.
 * Retorno: O numero da posicao na tabela, ou -1 se a senha nao esta na mesma.
 */
int buscar(Item* tabela, const char* senha);

#endif	/* _LABHASHING_H_ */

