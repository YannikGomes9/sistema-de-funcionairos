#include <stdio.h>

#include "persistencia.h"

void carregarArquivo(
    BancoFuncionarios *b)
{
    FILE *fp =
        fopen(
            "funcionarios.txt",
            "r"
        );

    if(fp==NULL)
        return;

    Funcionario f;

    while(
        fscanf(
            fp,
            "%d;%99[^;];%49[^;];%f",
            &f.id,
            f.nome,
            f.departamento,
            &f.salario
        ) == 4
    )
    {
        adicionarFuncionario(
            b,
            f
        );
    }

    fclose(fp);
}

void salvarArquivo(
    BancoFuncionarios *b)
{
    FILE *fp =
        fopen(
            "funcionarios.txt",
            "w"
        );

    if(fp==NULL)
        return;

    for(
        int i=0;
        i<b->quantidade;
        i++
    )
    {
        fprintf(
            fp,
            "%d;%s;%s;%.2f\n",
            b->funcionarios[i].id,
            b->funcionarios[i].nome,
            b->funcionarios[i].departamento,
            b->funcionarios[i].salario
        );
    }

    fclose(fp);
}