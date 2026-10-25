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
        int escolha;
        do
        {
            escolha = -1;
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║                   NOVA SOLICITAÇÃO                   ║\n");
            printf("  ║         Confira os dados antes de confirmar          ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║  Código da solicitação:  %-28d║\n", novo->CodSol);
            printf("  ║  Código do equipamento:  %-28s║\n", novo->CodEqu);
            printf("  ║  Nome do equipamento:    %-28s║\n", novo->NomEqu);
            printf("  ║  Prioridade:             %-28d║\n", novo->Priori);
            printf("  ║  Período (dias):         %-28d║\n", novo->Period);
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║  [1]  Confirmar cadastro                             ║\n");
            printf("  ║  [2]  Editar solicitação                             ║\n");
            printf("  ║  [3]  Cancelar solicitação                           ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Opção escolhida: ");
            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<1 || escolha >3)
               {
                    printf("\n  [ERRO] Opção inválida. Escolha entre 1 e 3.\n");
                    pause();
               }
        }while(escolha<1 || escolha >3);

        switch(escolha)
        {
        case 1:
            insereLista(p,novo);
            printf("\n  [OK] Solicitação cadastrada com sucesso.\n");
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
            printf("\n  [AVISO] Solicitação cancelada.\n");
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
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║              ENCERRAMENTO DE SOLICITAÇÃO             ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║  Informe o código da solicitação a ser encerrada.    ║\n");
            printf("  ║                                                      ║\n");
            printf("  ║  [1]  Retornar ao menu                               ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Código da solicitação: ");
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
                    if(removeLista(p,entrada))
                    {
                        printf("\n  [OK] Solicitação encerrada com sucesso.\n");
                        verifica = 1;
                    }
                    else
                    {
                        printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");
                    }
                }
                else
                {
                    printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");
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
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║                CONSULTA DE SOLICITAÇÃO               ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║  Informe o código da solicitação a ser consultada.   ║\n");
            printf("  ║                                                      ║\n");
            printf("  ║  [1]  Retornar ao menu                               ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Código da solicitação: ");

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
                        printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");
                    }
                }
                else
                {
                    printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");                }
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
            pause();
        }
        else
        {
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║               EDIÇÃO DE SOLICITAÇÃO                  ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║  Selecione a solicitação que deseja editar.          ║\n");
            printf("  ║                                                      ║\n");
            printf("  ║  [1]  Retornar ao menu                               ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Código da solicitação: ");

            scanf("%d",&entrada);
            limpar_buffer();

            if (entrada == 1)
            {
                verifica = 1;
                pause();
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
                        printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");
                        pause();
                    }
                }
                else
                {
                    printf("\n  [ERRO] Código de solicitação inválido ou inexistente.\n");
                    pause();
                }
            }
        }
    }while(verifica == 0);
}
void ExibirSol(Lista *p)
{
    No *aux = p -> inicio;

    if(aux == NULL)
    {
        printf("\n  [AVISO] Nenhuma solicitação em aberto.\n");
    }
    else
    {
        printf("\n");
        printf("  ╔══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                      ║\n");
        printf("  ║               SOLICITAÇÕES CADASTRADAS               ║\n");
        printf("  ║                                                      ║\n");

        while(aux != NULL)
        {
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║                                                      ║\n");
            printf("  ║  Código da solicitação:  %-27d ║\n", aux->CodSol);
            printf("  ║  Código do equipamento:  %-27s ║\n", aux->CodEqu);
            printf("  ║  Nome do equipamento:    %-27s ║\n", aux->NomEqu);
            printf("  ║  Prioridade:             %-27d ║\n", aux->Priori);
            printf("  ║  Período de manutenção:  %-27d ║\n", aux->Period);
            printf("  ║                                                      ║\n");
            aux = aux -> prox;
        }
        printf("  ╚══════════════════════════════════════════════════════╝\n");
    }
    pause();
}
void ExibirListaOrdemPriori(Lista *p)
{
    Lista *pAux = criaLista();

    No *aux = p -> inicio;

    if(aux == NULL)
    {
        printf("\n  [AVISO] Nenhuma solicitação em aberto.\n");
    }
    else
    {
        insereLista(pAux,copiaNo(aux));

        aux = aux -> prox;

        while(aux != NULL)
        {
            pAux -> inicio = insereListaCrescente(pAux, copiaNo(aux));
            aux = aux ->prox;
        }

        ExibirSol(pAux);
        liberaLista(pAux);
    }
}

void menu(Lista *p)
{
    int escolha;
    do
    {
        do
        {
            escolha = -1;
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║              MANUTENÇÃO DE EQUIPAMENTOS              ║\n");
            printf("  ║             Gerenciador de solicitações              ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [1]  Cadastrar nova solicitação                   ║\n");
            printf("  ║    [2]  Remover solicitação                          ║\n");
            printf("  ║    [3]  Consultar solicitação                        ║\n");
            printf("  ║    [4]  Alterar prioridade ou período                ║\n");
            printf("  ║    [5]  Exibir solicitações em ordem crescente       ║\n");
            printf("  ║    [6]  Exibir todas as solicitações                 ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [0]  Sair                                         ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n");
            printf("  >> Opção escolhida: ");
            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<0 || escolha >6)
               {
                    printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 6.\n");
                    pause();
               }
        }while(escolha<0 || escolha >6);

        switch(escolha)
        {
            case 0:
                printf("\n  [OK] Programa encerrado com sucesso.\n");
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

            case 6:
                pause();
                ExibirSol(p);
                break;
        }
    }while(escolha != 0);

}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Lista *p = criaLista();

    menu(p);

    liberaLista(p);

    return 0;
}

