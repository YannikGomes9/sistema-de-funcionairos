#ifndef HASHMAP_H
#define HASHMAP_H

#define HASH_SIZE 211

typedef struct NoHash
{
    int id;
    int posicao;

    struct NoHash *prox;

} NoHash;

typedef struct
{
    NoHash *tabela[HASH_SIZE];

} HashMap;

void inicializarHash(HashMap *h);

int inserirHash(
    HashMap *h,
    int id,
    int posicao
);

int buscarHash(
    HashMap *h,
    int id
);

int removerHash(
    HashMap *h,
    int id
);

#endif