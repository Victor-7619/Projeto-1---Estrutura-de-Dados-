#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"listLibr.h"

void InserirNovaSolicitacao(Lista *p)
{
    int code;
    char entrada[100];
    No *novo = (No*)malloc(sizeof(No));
    novo->prox = NULL;

    do
    {
        printf("codigo de solicitação: ");
        fgets(entrada,sizeof(entrada),stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if(strlen(entrada) != 4)
        {
            printf("\nDigite um código de 4 digitos.");
        }
        else
        {
            if(VerCod(p,entrada))
            {
                printf("\nCodigo de solicitação já cadastrado.");
            }
        }
        pause();
    }while(VerCod(p,entrada) || strlen(entrada) != 4);

    strcpy(novo->CodSol, entrada);

    do
    {
        printf("Digite o Código do Equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 7)
        {
            printf("\nDigite no maximo 20 caracteres!\n");
        }
        pause();
    }while(strlen(entrada) > 7);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->CodEqu, entrada);

    do
    {
        printf("Digite o Nome do equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 21)
        {
            printf("\nDigite no maximo 6 caracteres!\n");
        }
        pause();
    }while(strlen(entrada) > 21);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->NomEqu, entrada);

    do
    {
        printf("Digite o periodo de manutenção do equipamento: ");
        scanf("%d",&novo->Period);
        getchar();

        if(novo->Period<1 || novo->Period>20)
        {
            printf("\nPeriodo incorreto.");
        }
        pause();
    }while(novo->Period<1 || novo->Period>20);

    if(novo->Period>7)
    {
        if(novo->Period>15)
        {
            novo->Priori = 3;
        }
        else
        {
            novo->Priori = 2;
        }
    }
    else
    {
        novo->Priori = 1;
    }
    int escolha = -1;
    do
    {
        printf("-------Nova solicitação-------\n\n");
        printf("Código da solicitação: %s\n", novo->CodSol);
        printf("Código do equipamento:   %s\n", novo->CodEqu);
        printf("Nome do equipamento:      %s\n", novo->NomEqu);
        printf("Prioridade:               %d\n", novo->Priori);
        printf("Periodo de manutenção:  %d dias\n\n", novo->Period);
        printf("-------------------------------");
        printf("\n\n--Menu--");
        printf("\n1- Inserir solicitação");
        printf("\n2- Editar solicitação");
        printf("\n3 - excluir solicitação");
        printf("\n\nResposta: ");
        scanf("%d",&escolha);

        if(escolha<1 && escolha >3)
           {
                printf("\n--Escolha inválida--");
                pause();
           }
    }while(escolha<1 && escolha >3);

    switch(escolha)
    {
    case 1:
        insereLista(p,novo);
        printf("\nSolicitação cadastrada com sucesso.");
        pause();
        break;
    case 3:
        free(novo);
        printf("\nsolicitação cancelada.");
        pause();
        break;
    }
}
void RemoverSolicitacao(Lista *p)
{
    int verifica = 0;
    char entrada[6];

    do
    {
        imprimeSolicita(p);

        printf("\n\nDigite o código da solicitação a ser encerrada(1 para retornar ao menu): ");
        fgets(entrada,sizeof(entrada),stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strcmp(entrada, "1") == 0)
        {
            printf("\nRetornando ao menu.");
            verifica = 1;
        }
        else
        {
            if(strlen(entrada) == 4)
            {
                if(removeLista(p,entrada))
                {
                    printf("\nSolicitação encerrada com sucesso.");
                    verifica = 1;
                }
                else
                {
                    printf("codigo de solicitação inválido ou inexistente.");
                }
            }
            else
            {
                printf("codigo de solicitação inválido ou inexistente.");
            }
        }
        pause();
    }while(verifica == 0);
}
void consultaSolicitacao(Lista *p)
{
    int verifica = 0;
    char entrada[6];

    do
    {
        imprimeSolicita(p);

        printf("\n\nDigite o código da solicitação a ser consultada (1 para retornar ao menu): ");
        fgets(entrada,sizeof(entrada),stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strcmp(entrada, "1") == 0)
        {
            printf("\nRetornando ao menu.");
            verifica = 1;
        }
        else
        {
            if(strlen(entrada) == 4)
            {
                if(imprimeLista(p,entrada))
                {
                    verifica = 1;
                }
                else
                {
                    printf("codigo de solicitação inválido ou inexistente.");
                }
            }
            else
            {
                printf("codigo de solicitação inválido ou inexistente.");
            }
        }
        pause();
    }while(verifica == 0);
}
void menu(Lista *p)
{
    int escolha = -1;
    do
    {
        printf("----Gerenciador de Manutenção de Equipamentos----");
        printf("\n\n1- Insira uma nova solicitação");
        printf("\n2- Remova uma solicitação");
        printf("\n3- Consulte uma solicitação");
        printf("\n0- sair");
        printf("\n\n------------------------------------------------");
        printf("\nOpção escolhida: ");
        scanf("%d",&escolha);
        getchar();

        switch(escolha)
        {
            case 0:
                printf("Encerrando programa.");
                break;
            case 1:
                pause();
                InserirNovaSolicitacao(p);
                break;
            case 2:
                pause();
                RemoverSolicitacao(p);
                break;
            case 3:
                pause();
                consultaSolicitacao(p);
                break;
            default:
                escolha = -1;
                printf("\nEscolha inválida.");
                break;
        }
    }while(escolha != 0);

}
int main()
{
    setlocale(LC_ALL, "");
    Lista *p = criaLista();

    menu(p);

    return 0;
}

