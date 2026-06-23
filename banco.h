#ifndef BANCO_H
#define BANCO_H

#include "funcionario.h"
#include "hash_map.h"

#define MAX_FUNCIONARIOS 1000

typedef struct
{
    Funcionario funcionarios[MAX_FUNCIONARIOS];

    int quantidade;

    HashMap indiceID;

} BancoFuncionarios;

void inicializarBanco(
    BancoFuncionarios *b
);

int adicionarFuncionario(
    BancoFuncionarios *b,
    Funcionario f
);

Funcionario* buscarFuncionarioID(
    BancoFuncionarios *b,
    int id
);

int removerFuncionario(
    BancoFuncionarios *b,
    int id
);

void listarFuncionarios(
    BancoFuncionarios *b
);

void buscarNomeParcial(
    BancoFuncionarios *b,
    const char *nome
);

void ordenarPorNome(
    BancoFuncionarios *b
);

void ordenarPorSalario(
    BancoFuncionarios *b
);

void contarDepartamentos(
    BancoFuncionarios *b
);

void folhaSalarial(
    BancoFuncionarios *b
);

void reconstruirHash(
    BancoFuncionarios *b
);

#endif