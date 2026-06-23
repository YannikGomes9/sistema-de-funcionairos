#include <stdio.h>
#include <string.h>
#include "funcionario.h"

Funcionario criarFuncionario(
    int id,
    const char *nome,
    const char *dep,
    float salario)
{
    Funcionario f;

    f.id = id;

    strcpy(f.nome,nome);
    strcpy(f.departamento,dep);

    f.salario = salario;

    return f;
}

void imprimirFuncionario(Funcionario f)
{
    printf("\n");
    printf("ID: %d\n",f.id);
    printf("Nome: %s\n",f.nome);
    printf("Departamento: %s\n",f.departamento);
    printf("Salario: %.2f\n",f.salario);
}