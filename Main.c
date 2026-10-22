#include"listLibr.h"

void InserirNovaSolicitacao(Lista *p)
{
    int verifica = 0;
    char entrada[100];
    No *novo = (No*)malloc(sizeof(No));
    novo->prox = NULL;

    insereCodSol(p,novo);
    insereCodEqu(p,novo);
    insereNomEqu(p,novo);
    inserePriori(p,novo);

    pause();
    do
    {
        int escolha = -1;
        do
        {
            printf("\t\t\t------------------------------------------");
            printf("\n\t\t\t|           Nova Solicitação           |");
            printf("\n\t\t\t------------------------------------------");
            printf("\n\t\t\t Código da solicitação: %d\n", novo->CodSol);
            printf("\n\t\t\t Código do equipamento:   %s\n", novo->CodEqu);
            printf("\n\t\t\t Nome do equipamento:      %s\n", novo->NomEqu);
            printf("\n\t\t\t Prioridade:               %d\n", novo->Priori);
            printf("\n\t\t\t Periodo de manutenção:  %d dia(s)\n\n", novo->Period);
            printf("\t\t\t------------------------------------------");
            printf("\n\t\t\t            |      Menu      |");
            printf("\n\t\t\t            ------------------\n");
            printf("\n\t\t\t\t [1] Inserir solicitação");
            printf("\n\t\t\t\t [2] Editar solicitação");
            printf("\n\t\t\t\t [3] Excluir solicitação");
            printf("\n\n\t\t\t Resposta: ");
            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<1 || escolha >3)
               {
                    printf("\n\t\t\t--Escolha inválida--");
                    pause();
               }
        }while(escolha<1 || escolha >3);

        switch(escolha)
        {
        case 1:
            insereLista(p,novo);
            printf("\n\t\t\tSolicitação cadastrada com sucesso.");
            pause();
            verifica = 0;
            break;

        case 2:
            pause();
            editaInfo(p,novo);
            verifica = 1;
            break;

        case 3:
            free(novo);
            printf("\n\t\t\tsolicitação cancelada.");
            pause();
            verifica = 0;
            break;
        }
    }while(verifica == 1);

}
void RemoverSolicitacao(Lista *p)
{
    int verifica = 0;
    int entrada;

    do
    {
        if(!imprimeSolicita(p))
        {
            verifica = 1;
        }
        else
        {
            printf("\n\n\t\t\tDigite o código da solicitação a ser encerrada (1 para retornar ao menu): ");
            scanf("%d",&entrada);

            if (entrada == 1)
            {
                verifica = 1;
            }
            else
            {
                if(entrada >= 1000 && entrada <= 9999)
                {
                    if(removeLista(p,entrada))
                    {
                        printf("\n\t\t\tSolicitação encerrada com sucesso.");
                        verifica = 1;
                    }
                    else
                    {
                        printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                    }
                }
                else
                {
                    printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                }
            }
        }
        pause();
    }while(verifica == 0);
}
void consultaSolicitacao(Lista *p)
{
    int verifica = 0;
    int entrada;
    do
    {
        if(!imprimeSolicita(p))
        {
            verifica = 1;
        }
        else
        {
            printf("\n\n\t\t\tDigite o código da solicitação a ser consultada (1 para retornar ao menu): ");
            scanf("%d",&entrada);
            limpar_buffer();

            if (entrada == 1)
            {
                verifica = 1;
            }
            else
            {
                if(entrada >= 1000 && entrada <= 9999)
                {
                    if(imprimeLista(p,entrada))
                    {
                        verifica = 1;
                    }
                    else
                    {
                        printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                    }
                }
                else
                {
                    printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                }
            }
        }
        pause();
    }while(verifica == 0);
}
void alteraPeriodOrPriori(Lista *p)
{
    int verifica = 0;
    int entrada;
    do
    {
        if(!imprimeSolicita(p))
        {
            verifica = 1;
        }
        else
        {
            printf("\n\n\t\t\tDigite o código da solicitação a ser editado (1 para retornar ao menu): ");
            scanf("%d",&entrada);
            limpar_buffer();

            if (entrada == 1)
            {
                verifica = 1;
            }
            else
            {
               if(entrada >= 1000 && entrada <= 9999)
                {
                    if(editaLista(p,entrada))
                    {
                        verifica = 1;
                    }
                    else
                    {
                        printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                    }
                }
                else
                {
                    printf("\t\t\tcodigo de solicitação inválido ou inexistente.");
                }
            }
        }
    }while(verifica == 0);
}
void ExibirSol(Lista *p)
{
    No *aux = p -> inicio;

        printf("\t\t\t-------------------------------------------");
        printf("\n\t\t\t|           Menu Solicitações           |");
        printf("\n\t\t\t-------------------------------------------");

    while(aux != NULL)
    {
        printf("\n\n    \t\t\t Código da solicitação: %d\n", aux->CodSol);
        printf("\n\t\t\t Código do equipamento:   %s\n", aux->CodEqu);
        printf("\n\t\t\t Nome do equipamento:      %s\n", aux->NomEqu);
        printf("\n\t\t\t Prioridade:               %d\n", aux->Priori);
        printf("\n\t\t\t Periodo de manutenção:  %d dia(s)\n\n", aux->Period);
        printf("\t\t\t------------------------------------------\n\n\n");
        aux = aux -> prox;
    }
    pause();
}
void ExibirListaOrdemPriori(Lista *p)
{
    Lista *pAux = criaLista();

    No *aux = p -> inicio;

    insereLista(pAux,copiaNo(aux));

    aux = aux -> prox;

    while(aux != NULL)
    {
        pAux -> inicio = insereListaCrescente(pAux, copiaNo(aux));
        aux = aux ->prox;
    }
    ExibirSol(pAux);
}
void menu(Lista *p)
{
    int escolha = -1;
    do
    {
        do
        {
            printf("\t\t\t---------------------------------------------------------");
            printf("\n\t\t\t|      Gerenciador de Manutenção de Equipamentos      |");
            printf("\n\t\t\t---------------------------------------------------------");
            printf("\n\n\t\t\t [1] Insira uma nova solicitação");
            printf("\n\t\t\t [2] Remova uma solicitação");
            printf("\n\t\t\t [3] Consulte uma solicitação");
            printf("\n\t\t\t [4] Altere a prioridade e/ou período de uma Solicitação");
            printf("\n\t\t\t [5] Exibir solicitações");
            printf("\n\t\t\t [0] sair");
            printf("\n\n\t\t\t---------------------------------------------------------");
            printf("\n\t\t\t Opção escolhida: ");
            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<0 || escolha >5)
               {
                    printf("\n\t\t\t--Escolha inválida--");
                    pause();
               }
        }while(escolha<0 || escolha >5);

        switch(escolha)
        {
            case 0:
                printf("\t\t\tEncerrando programa.");
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

            case 4:
                pause();
                alteraPeriodOrPriori(p);
                break;

            case 5:
                pause();
                ExibirListaOrdemPriori(p);
                break;
        }
    }while(escolha != 0);

}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Lista *p = criaLista();

    menu(p);

    return 0;
}

