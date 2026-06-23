#include <stdlib.h>
#include "hash_map.h"

/* Função de hash simples para mapear IDs em índices fixos. */
static int funcaoHash(int id)
{
    return id % HASH_SIZE;
}

void inicializarHash(HashMap *h)
{
    for(int i=0;i<HASH_SIZE;i++)
        h->tabela[i]=NULL;
}

/* Insere um par ID-posicao no mapa hash para busca rápida. */
int inserirHash(
    HashMap *h,
    int id,
    int posicao)
{
    int indice = funcaoHash(id);

    NoHash *novo =
        (NoHash*) malloc(sizeof(NoHash));

    if(novo==NULL)
        return 0;

    novo->id=id;
    novo->posicao=posicao;

    novo->prox=h->tabela[indice];

    h->tabela[indice]=novo;

    return 1;
}

/* Busca um ID no map hash e retorna a posição correspondente ou -1 se não existir. */
int buscarHash(
    HashMap *h,
    int id)
{
    int indice = funcaoHash(id);

    NoHash *aux =
        h->tabela[indice];

    while(aux)
    {
        if(aux->id==id)
            return aux->posicao;

        aux=aux->prox;
    }

    return -1;
}

/* Remove um par ID-posicao do mapa hash, ajustando os ponteiros da lista encadeada. */
int removerHash(
    HashMap *h,
    int id)
{
    int indice = funcaoHash(id);

    NoHash *atual=h->tabela[indice];
    NoHash *anterior=NULL;

    while(atual)
    {
        if(atual->id==id)
        {
            if(anterior)
                anterior->prox=atual->prox;
            else
                h->tabela[indice]=atual->prox;

            free(atual);
            return 1;
        }

        anterior=atual;
        atual=atual->prox;
    }

    return 0;
}