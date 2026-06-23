#include <stdio.h>
#include <string.h>
#include "banco.h"

void inicializarBanco(
    BancoFuncionarios *b)
{
    b->quantidade=0;

    inicializarHash(
        &b->indiceID
    );
}

int adicionarFuncionario(
    BancoFuncionarios *b,
    Funcionario f)
{
    if(b->quantidade>=MAX_FUNCIONARIOS)
    {
        printf("Falha: banco cheio.\n");
        return 0;
    }

    if(buscarHash(
        &b->indiceID,
        f.id)!=-1)
    {
        printf("Falha: ID existente.\n");
        return 0;
    }

    int pos=b->quantidade;

    b->funcionarios[pos]=f;

    inserirHash(
        &b->indiceID,
        f.id,
        pos
    );

    b->quantidade++;

    printf("Sucesso: funcionario inserido.\n");

    return 1;
}

Funcionario* buscarFuncionarioID(
    BancoFuncionarios *b,
    int id)
{
    int pos=
        buscarHash(
            &b->indiceID,
            id
        );

    if(pos==-1)
        return NULL;

    return &b->funcionarios[pos];
}

void buscarNomeParcial(
    BancoFuncionarios *b,
    const char *nome)
{
    int encontrou=0;

    for(int i=0;i<b->quantidade;i++)
    {
        if(strstr(
            b->funcionarios[i].nome,
            nome))
        {
            imprimirFuncionario(
                b->funcionarios[i]
            );

            encontrou=1;
        }
    }

    if(!encontrou)
        printf("Nenhum encontrado.\n");
}

void listarFuncionarios(
    BancoFuncionarios *b)
{
    if(b->quantidade==0)
    {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    printf("\n+-------+---------------------------+-----------------+---------------+\n");
    printf("| ID    | Nome                      | Departamento    | Salario       |\n");
    printf("+-------+---------------------------+-----------------+---------------+\n");

    for(int i=0;i<b->quantidade;i++)
    {
        printf("| %-5d | %-25s | %-15s | R$ %.2f        |\n",
               b->funcionarios[i].id,
               b->funcionarios[i].nome,
               b->funcionarios[i].departamento,
               b->funcionarios[i].salario);
    }

    printf("+-------+---------------------------+-----------------+---------------+\n");
    printf("Total: %d funcionario(s).\n", b->quantidade);
}

void folhaSalarial(
    BancoFuncionarios *b)
{
    float total=0;

    for(int i=0;i<b->quantidade;i++)
        total+=b->funcionarios[i].salario;

    if(b->quantidade==0)
    {
        printf("Sem funcionarios.\n");
        return;
    }

    printf(
        "Total: %.2f\n",
        total
    );

    printf(
        "Media: %.2f\n",
        total/b->quantidade
    );
}

int removerFuncionario(
    BancoFuncionarios *b,
    int id)
{
    int pos = buscarHash(&b->indiceID, id);

    if(pos == -1)
    {
        printf("Falha: funcionario nao encontrado.\n");
        return 0;
    }

    for(int i=pos;i<b->quantidade-1;i++)
    {
        b->funcionarios[i] = b->funcionarios[i+1];
    }

    b->quantidade--;
    reconstruirHash(b);

    printf("Sucesso: funcionario removido.\n");

    return 1;
}

void ordenarPorNome(
    BancoFuncionarios *b)
{
    if(b->quantidade <= 1)
        return;

    for(int i=0;i<b->quantidade-1;i++)
    {
        for(int j=0;j<b->quantidade-i-1;j++)
        {
            if(strcmp(
                b->funcionarios[j].nome,
                b->funcionarios[j+1].nome) > 0)
            {
                Funcionario temp = b->funcionarios[j];
                b->funcionarios[j] = b->funcionarios[j+1];
                b->funcionarios[j+1] = temp;
            }
        }
    }

    reconstruirHash(b);
}

void ordenarPorSalario(
    BancoFuncionarios *b)
{
    if(b->quantidade <= 1)
        return;

    for(int i=0;i<b->quantidade-1;i++)
    {
        for(int j=0;j<b->quantidade-i-1;j++)
        {
            if(b->funcionarios[j].salario >
               b->funcionarios[j+1].salario)
            {
                Funcionario temp = b->funcionarios[j];
                b->funcionarios[j] = b->funcionarios[j+1];
                b->funcionarios[j+1] = temp;
            }
        }
    }

    reconstruirHash(b);
}

void contarDepartamentos(
    BancoFuncionarios *b)
{
    if(b->quantidade==0)
    {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    typedef struct
    {
        char departamento[MAX_DEP];
        int quantidade;
    } DeptCount;

    DeptCount depts[100];
    int numDepts = 0;

    for(int i=0;i<b->quantidade;i++)
    {
        int encontrou = 0;

        for(int j=0;j<numDepts;j++)
        {
            if(strcmp(depts[j].departamento, b->funcionarios[i].departamento) == 0)
            {
                depts[j].quantidade++;
                encontrou = 1;
                break;
            }
        }

        if(!encontrou)
        {
            strcpy(depts[numDepts].departamento, b->funcionarios[i].departamento);
            depts[numDepts].quantidade = 1;
            numDepts++;
        }
    }

    printf("\n+-----------------+------------+\n");
    printf("| Departamento    | Funcionarios |\n");
    printf("+-----------------+------------+\n");

    for(int i=0;i<numDepts;i++)
    {
        printf("| %-15s | %-10d |\n",
               depts[i].departamento,
               depts[i].quantidade);
    }

    printf("+-----------------+------------+\n");
    printf("Total: %d departamento(s).\n", numDepts);
}

void reconstruirHash(
    BancoFuncionarios *b)
{
    inicializarHash(&b->indiceID);

    for(int i=0;i<b->quantidade;i++)
    {
        inserirHash(
            &b->indiceID,
            b->funcionarios[i].id,
            i
        );
    }
}

