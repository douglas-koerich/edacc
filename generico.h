#ifndef GENERICO_H
#define GENERICO_H

typedef struct generico {
    void* coisa;
    void (*imprime)(void*);
} generico;

#endif

