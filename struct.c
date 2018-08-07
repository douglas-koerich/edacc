// Definicao da estrutura ("modelo" do registro)

#define NUM_MESES 6 // ultimos 6 meses no historico do consumidor

struct consumidor {
    // Campos da estrutura
    int codigo; // "Chave" do registro (vai identificar de maneira unica um registro entre outros)
    char tipo;  // 'R' para residencial, 'C' para comercial, 'I' para industrial
    float historico_medidas[NUM_MESES];
    float valor_conta;
};  // nao esquecer o ponto-e-virgula
typedef struct consumidor Consumidor;   // novo nome para o tipo-registro

#include <stdio.h>
#include <ctype.h>

float calcula_media(float [*], size_t);

// Programa para cadastro de consumidores
int main(void) {
    // Variavel de entrada para um novo consumidor cadastrado
    struct consumidor cons; // 'cons' eh o nome da variavel, do tipo 'struct consumidor'

    // Preenche os dados do consumidor
    printf("Digite o codigo do consumidor: ");
    scanf("%d", &cons.codigo);
    char t;
    do {
        printf("Digite o tipo (R/C/I): ");
        scanf(" %c", &t);
        t = toupper(t); // converte pra maiuscula
    } while (t != 'R' && t != 'C' && t != 'I');
    cons.tipo = t;
    int indice;
    for (indice = 0; indice < NUM_MESES; ++indice) {
        printf("Digite a medida do mes anterior [%d]: ", indice);
        scanf("%f", &cons.historico_medidas[indice]);
    }
    printf("Digite o valor da conta: ");
    scanf("%f", &cons.valor_conta);

    // Calcula a media das medidas dos meses anteriores
    float media = calcula_media(cons.historico_medidas, NUM_MESES);
    printf("A media das medidas anteriores eh %f.\n", media);

    // Cadastro maior ("banco de dados");
    Consumidor cadastro[3];  // tres consumidores/registros no banco

    // Media do cadastro sera calculada sobre o historico de TODOS os consumidores
    media = 0.0;

    for (indice = 0; indice < 3; ++indice) {    // um laco para o vetor de registros
        printf("Digite o codigo do consumidor #%d: ", indice+1);
        scanf("%d", &cadastro[indice].codigo);
        do {
            printf("Digite o tipo (R/C/I): ");
            scanf(" %c", &t);
            t = toupper(t); // converte pra maiuscula
        } while (t != 'R' && t != 'C' && t != 'I');
        cadastro[indice].tipo = t;
        int i;
        for (i = 0; i < NUM_MESES; ++i) {
            printf("Digite a medida do mes anterior [%d]: ", i);
            scanf("%f", &cadastro[indice].historico_medidas[i]);
            media += cadastro[indice].historico_medidas[i]; // totaliza com essa medida
        }
        printf("Digite o valor da conta: ");
        scanf("%f", &cadastro[indice].valor_conta);
    }
    media = media / (NUM_MESES * 3);
    printf("A media geral do cadastro eh %f.\n", media);

    return 0;
}

float calcula_media(float v[], size_t tam) {
    float media = 0.0;
    int ind = 0;
    while (ind < tam) {
        media += v[ind];
        ++ind;
    }
    return media / tam;
}

