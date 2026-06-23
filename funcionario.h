#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#define MAX_NOME 100
#define MAX_DEP 50

typedef struct
{
    int id;
    char nome[MAX_NOME];
    char departamento[MAX_DEP];
    float salario;

} Funcionario;

Funcionario criarFuncionario(
    int id,
    const char *nome,
    const char *dep,
    float salario
);

void imprimirFuncionario(Funcionario f);

#endif