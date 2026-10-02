#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"listLibr.h"   

void InserirNovaSolicitacao(Lista *p)
{
    int code,existe;
    char entrada[100];
    No *novo = (No*)malloc(sizeof(No));
    novo->prox = NULL;

    do
    {
        printf("codigo de solicitação: ");
        scanf("%d",&code);
        getchar();

        existe = VerCod(p,code);
        
        if(existe)
        {
            printf("Codigo de solicitação já cadastrado.");
            system("pause");
            system("cls");
        }
    }while(existe);

    novo->CodSol = code;

    do
    {
        printf("Digite o Código do Equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 7)
        {
            printf("Digite no maximo 20 caracteres!\n");
        }
    }while(strlen(entrada) > 7);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->CodEqu, entrada);

    do
    {
        printf("Digite o Nome do equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 21)
        {
            printf("Digite no maximo 6 caracteres!\n");
        }
    }while(strlen(entrada) > 21);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->NomEqu, entrada);

    do
    {
        printf("\nDigite o periodo de manutenção do equipamento: ");
        scanf("%d",&novo->Period);

        if(novo->Period<1 || novo->Period>20)
        {
            printf("\n\nPeriodo incorreto.");
            system("pause");
            system("cls");
        }
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

    //Printar info do no para o usuario confirmar os dados

    insereLista(p,novo);
}

int main()
{
    Lista *p = criaLista();

    InserirNovaSolicitacao(p);
    ImprimeLista(p);

    return 0;
}

