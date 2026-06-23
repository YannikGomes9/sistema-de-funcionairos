#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "funcionario.h"
#include "hash_map.h"
#include "banco.h"
#include "persistencia.h"
#include "console.h"

/* Função principal: executa o menu de operações, carrega dados persistidos e salva ao sair. */
int main()
{
    BancoFuncionarios banco;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    inicializarBanco(&banco);

    carregarArquivo(&banco);

    int opcao;

    do
    {
        printf("\n");
        printf("=========================================================\n");
        printf("           SISTEMA DE FUNCIONÁRIOS - MENU PRINCIPAL      \n");
        printf("=========================================================\n");
        printf("|  1  | Adicionar funcionário                             |\n");
        printf("|  2  | Listar todos os funcionários                      |\n");
        printf("|  3  | Buscar por ID                                     |\n");
        printf("|  4  | Buscar por nome                                   |\n");
        printf("|  5  | Atualizar dados do funcionário                     |\n");
        printf("|  6  | Remover funcionário                                |\n");
        printf("|  7  | Folha salarial                                     |\n");
        printf("|  8  | Ordenar por nome                                   |\n");
        printf("|  9  | Ordenar por salário                                |\n");
        printf("| 10  | Contar departamentos                               |\n");
        printf("|  0  | Sair                                               |\n");
        printf("=========================================================\n");
        printf("Opção: ");

        scanf("%d",&opcao);
        printf("---------------------------------------------------------\n");

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
                    printError("Falha: funcionário não encontrado.\n");
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
                    printError("Falha: funcionário não encontrado.\n");
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

                printSuccess("Funcionário atualizado com sucesso.\n");

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

                printSuccess("Funcionários ordenados por nome.\n");

                salvarArquivo(&banco);
                break;
            }
            case 9:
            {
                /* Ordenar Salario */
                ordenarPorSalario(&banco);

                printSuccess("Funcionários ordenados por salário.\n");

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

                printInfo("Sistema encerrado.\n");
                break;
            }
            default:
    
                printError("Opção inválida.\n");
        }

    }while(opcao!=0);

    salvarArquivo(&banco);

    return 0;
}