#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "hash_map.h"
#include "banco.h"
#include "persistencia.h"

int main()
{
    BancoFuncionarios banco;

    inicializarBanco(&banco);

    carregarArquivo(&banco);

    int opcao;

    do
    {
        printf("\n");
        printf("1-Adicionar\n");
        printf("2-Listar\n");
        printf("3-Buscar ID\n");
        printf("4-Buscar Nome\n");
        printf("5-Atualizar\n");
        printf("6-Remover\n");
        printf("7-Folha Salarial\n");
        printf("8-Ordenar Nome\n");
        printf("9-Ordenar Salario\n");
        printf("10-Contar Departamentos\n");
        printf("0-Sair\n");

        scanf("%d",&opcao);

        switch(opcao)
        {
           case 1:
           {
                int id;
                char nome[100];
                char departamento[50];
                float salario;

                printf("ID: ");
                scanf("%d",&id);

                getchar();

                printf("Nome: ");
                fgets(nome,sizeof(nome),stdin);
                nome[strcspn(nome,"\n")] = '\0';

                printf("Departamento: ");
                fgets(departamento,sizeof(departamento),stdin);
                departamento[strcspn(departamento,"\n")] = '\0';

                printf("Salario: ");
                scanf("%f",&salario);

                Funcionario ff =
                    criarFuncionario(
                        id,
                        nome,
                        departamento,
                        salario
                    );

                adicionarFuncionario(
                    &banco,
                    ff
                );

                salvarArquivo(&banco);

                break;
            }
            case 2:
            {
                /* Listar */
                listarFuncionarios(&banco);
                break;
            }
            case 3:
            {
                /* Buscar ID */
                int searchId;

                printf("ID a procurar: ");
                scanf("%d",&searchId);

                Funcionario *f =
                    buscarFuncionarioID(
                        &banco,
                        searchId
                    );

                if(f)
                {
                    imprimirFuncionario(*f);
                }
                else
                {
                    printf("Falha: funcionario nao encontrado.\n");
                }
                break;
            }

            case 4:
            {
                /* Buscar Nome */
                char searchName[100];

                getchar();

                printf("Nome (ou parte dele): ");

                fgets(searchName,sizeof(searchName),stdin);

                searchName[strcspn(searchName,"\n")] = '\0';

                buscarNomeParcial(
                    &banco,
                    searchName
                );
                break;
            }

            case 5:
            {
                /* Atualizar */
                int updateId;

                printf("ID do funcionario: ");
                scanf("%d",&updateId);

                Funcionario *updateFuncionario =
                    buscarFuncionarioID(
                        &banco,
                        updateId
                    );

                if(updateFuncionario == NULL)
                {
                    printf("Falha: funcionario nao encontrado.\n");
                    break;
                }

                printf("\nDados atuais:\n");
                imprimirFuncionario(*updateFuncionario);

                getchar();

                printf("\nNovo nome: ");
                fgets(updateFuncionario->nome,sizeof(updateFuncionario->nome),stdin);
                updateFuncionario->nome[strcspn(updateFuncionario->nome,"\n")] = '\0';

                printf("Novo departamento: ");
                fgets(
                    updateFuncionario->departamento,
                    sizeof(updateFuncionario->departamento),
                    stdin
                );

                updateFuncionario->departamento[
                    strcspn(
                        updateFuncionario->departamento,
                        "\n"
                    )
                ] = '\0';

                printf("Novo salario: ");
                scanf("%f",&updateFuncionario->salario);

                printf("Sucesso: funcionario atualizado.\n");

                salvarArquivo(&banco);
                break;
            }

            case 6:
            {
                /* Remover */
                int id;

                printf("ID a remover: ");
                scanf("%d",&id);

                removerFuncionario(
                    &banco,
                    id
                );

                salvarArquivo(&banco);
                break;
            }
            case 7:
            {
                /* Folha Salarial */
                folhaSalarial(&banco);
                break;
            }
            case 8:
            {
                /* Ordenar Nome */
                ordenarPorNome(&banco);

                printf(
                    "Sucesso: funcionarios ordenados por nome.\n"
                );

                salvarArquivo(&banco);
                break;
            }
            case 9:
            {
                /* Ordenar Salario */
                ordenarPorSalario(&banco);

                printf(
                    "Sucesso: funcionarios ordenados por salario.\n"
                );

                salvarArquivo(&banco);

                break;
            }
            case 10:
            {
                /* Contar Departamentos */
                contarDepartamentos(&banco);
                break;
            }
            case 0:
            {

                salvarArquivo(&banco);

                printf("Sistema encerrado.\n");
                break;
            }
            default:
    
                printf("Opcao invalida.\n");
        }

    }while(opcao!=0);

    salvarArquivo(&banco);

    return 0;
}