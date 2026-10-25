#include"listLibr.h"

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

