#ifndef RECORD_H
#define RECORD_H

struct Record_ {
    int key;    // chave de identificacao do registro
    char value; // qualquer campo associado a essa chave...
    /* ... e mais outros campos (se existirem) ... */
};
typedef struct Record_ Record;

#endif  // RECORD_H