#ifndef FILA_USO_INTERNO_H_
#define FILA_USO_INTERNO_H_

struct Fila {
    int* vetor; // ponteiro para o vetor alocado com o tamanho pedido
    size_t tamanho; // salva o tamanho solicitado no momento da criacao
    int inicio, fim; // indices dos extremos da fila dentro do vetor "circular"
};

#endif // FILA_USO_INTERNO_H_
