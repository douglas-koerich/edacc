#ifndef DEQUE_USO_INTERNO_H_
#define DEQUE_USO_INTERNO_H_

struct Deque {
    int* vetor; // ponteiro para o vetor alocado com o tamanho pedido
    size_t tamanho; // salva o tamanho solicitado no momento da criacao
    int inicio, fim; // indices dos extremos do deque dentro do vetor "circular"
};

#endif // DEQUE_USO_INTERNO_H_
