#ifndef LISTLIBR_H_INCLUDED
#define LISTLIBR_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
// STRUCT'S
typedef struct no
{
        int CodSol;
        char CodEqu[7];
        char NomEqu[21];
        int Priori;
        int Period;
        struct no *prox;
}No;
typedef struct lista
{
    No *inicio;
}Lista;


// INICIALIZAÇAO/LIBERAÇAO DE LISTA

void limpar_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
Lista* inicializaLista()
{
    return NULL;
}
Lista* criaLista()
{
    Lista* aux;
    aux = (Lista*)malloc(sizeof(Lista));
    aux->inicio = NULL;
    return aux;
}
int vaziaLista(Lista *L)
{
    if(L->inicio==NULL)
    {
        return 1;
    }
    return 0;
}
Lista* liberaLista(Lista* L)
{
    No *aux = L->inicio, *aux2;

    while(aux!=NULL)
    {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(L);
    return NULL;
}


// COMANDOS PARA INSERIR NA LISTA
// Auxiliares
void pause()
{
    printf("\n\n");
    system("pause");
    system("cls");
}
int confereTam(No* antigo)
{
    int cont = 0;
    while(antigo!=NULL)
    {
        cont++;
        antigo = antigo->prox;
    }
    return cont;
}
int devePreceder(No *novo, No *atual)
{
    if(novo -> Priori != atual -> Priori)
    {
        if(novo -> Priori < atual -> Priori)
        {
            return 1;
        }
        return 0;
    }

    if(novo -> Period != atual -> Period)
    {
        if(novo -> Period < atual -> Period)
        {
            return 1;
        }
        return 0;
    }

    if(novo -> CodSol < atual -> CodSol)
    {
        return 1;
    }
    return 0;
}
No *insereListaCrescente(Lista *p, No *novo)
{
    No *aux = NULL;
    No *aux2 = p -> inicio;

    while(aux2 != NULL && !devePreceder(novo, aux2))
    {
        aux = aux2;
        aux2 = aux2 -> prox;
    }

    novo -> prox = aux2;

    if(aux == NULL)
    {
        return novo;
    }

    aux -> prox = novo;
    return p -> inicio;
}
No *auxInsere(No *antigo,No *novo)
{
    No *aux = NULL,*aux2 = antigo;

    while(aux2 != NULL && aux2 -> CodSol < novo -> CodSol)
    {
        aux = aux2;
        aux2 = aux2->prox;
    }
    if(aux == NULL)
    {
        novo -> prox = aux2;
        return novo;
    }
    aux -> prox = novo;
    novo -> prox = aux2;
    return antigo;
}
No *auxRemove(No *antigo, int entrada,int *verifica)
{
    No *novo = NULL,*aux = antigo;
    while(aux != NULL && aux -> CodSol != entrada)
    {
        novo = aux;
        aux = aux -> prox;
    }
    if(novo == NULL)
    {
        novo = aux -> prox;
        free(aux);
        *verifica = 1;
        return novo;
    }
    if(aux != NULL)
    {
        if(aux -> CodSol == entrada)
           {
               novo -> prox = aux -> prox;
               free(aux);
               *verifica = 1;
               return antigo;
           }
    }
    return antigo;
}
int VerCod(Lista *p, int n)
{
    No *aux = p->inicio;

    while(aux != NULL)
    {
        if(n == aux -> CodSol)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}
No* copiaNo(No *antigo)
{
    No *novo = (No*)malloc(sizeof(No));

    strcpy(novo -> CodEqu, antigo -> CodEqu);
    strcpy(novo -> NomEqu, antigo -> NomEqu);
    novo -> CodSol = antigo -> CodSol;
    novo -> Priori = antigo -> Priori;
    novo -> Period = antigo -> Period;
    novo -> prox = NULL;

    return novo;
}

//Inserir infos
void insereCodSol(Lista *p, No *novo)
{
    int verifica, entrada;
    do
    {
        entrada = 1;
        verifica = 0;

        printf("\n  [01/05] CÓDIGO DA SOLICITAÇÃO\n");
        printf("  > Informe o código (1000 a 9999): ");

        scanf("%d",&entrada);
        limpar_buffer();

        if(entrada < 1000 || entrada > 9999)
        {
            verifica = 1;
            printf("\n  [ERRO] O código deve conter 4 dígitos.\n");
            pause();
        }
        else
        {
            novo -> CodSol = entrada;
            if(VerCod(p,novo -> CodSol))
            {
                verifica = 1;
                printf("\n  [ERRO] Código já cadastrado.\n");
                pause();
            }
        }
    }while(verifica == 1);

}
void insereCodEqu(Lista *p, No *novo)
{
    char entrada[100];
    int valido;
    int i;

    do
    {
        printf("\n  [02/05] CÓDIGO DO EQUIPAMENTO\n");
        printf("  > Informe o código (3 letras e 3 números): ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        valido = (strlen(entrada) == 6);

        // posições 0, 1 e 2: letras de a até z ou A até Z
        for(i = 0; valido && i < 3; i++)
        {
            if(!((entrada[i] >= 'a' && entrada[i] <= 'z') || (entrada[i] >= 'A' && entrada[i] <= 'Z')))
                valido = 0;
        }

        // posições 3, 4 e 5: dígitos de 0 até 9
        for(i = 3; valido && i < 6; i++)
        {
            if(entrada[i] < '0' || entrada[i] > '9')
                valido = 0;
        }

        if(!valido)
        {
            printf("\n  [ERRO] O código deve ter 3 letras seguidas de 3 números.\n");
            pause();
        }
    } while(!valido);

    strcpy(novo->CodEqu, entrada);
}
void insereNomEqu(Lista *p,No *novo)
{
    char entrada[100];
    do
    {
        printf("\n  [03/05] NOME DO EQUIPAMENTO\n");
        printf("  > Informe o nome (máximo 20 caracteres): ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 21)
        {
            printf("\n  [ERRO] O nome deve conter no máximo 20 caracteres.\n");
            pause();
        }
    }while(strlen(entrada) > 21);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->NomEqu, entrada);
}
void inserePeriod(Lista *p,No *novo)
{
        switch(novo -> Priori)
        {
            case 1:
                do
                {
                    novo -> Period = -1;
                    printf("\n  [05/05] PERÍODO DE MANUTENÇÃO\n");
                    printf("  > Informe o período (1 a 7 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 7)
                    {
                        printf("\n  [ERRO] O período deve estar entre 1 e 7 dias.\n");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 7);
                break;

            case 2:
                do
                {
                    novo -> Period = -1;
                    printf("\n  [05/05] PERÍODO DE MANUTENÇÃO\n");
                    printf("  > Informe o período (1 a 15 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 15)
                    {
                        printf("\n  [ERRO] O período deve estar entre 1 e 15 dias.\n");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 15);
                break;

            case 3:
                do
                {
                    novo -> Period = -1;
                    printf("\n  [05/05] PERÍODO DE MANUTENÇÃO\n");
                    printf("  > Informe o período (1 a 20 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 20)
                    {
                        printf("\n  [ERRO] O período deve estar entre 1 e 20 dias.\n");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 20);
                break;
        }
}
int inserePriori(Lista *p, No *novo)
{
    int valor;
    do
    {
        printf("\n  [04/05] PRIORIDADE DA MANUTENÇÃO\n");
        printf("  > Informe a prioridade (1 a 3): ");
        scanf("%d",&valor);
        limpar_buffer();

        if(valor < 1 || valor > 3)
        {
            printf("\n  [ERRO] Prioridade inválida. Informe um valor entre 1 e 3.\n");
            pause();
        }
    }while(valor < 1 || valor > 3);

    if(valor != novo -> Priori)
    {
        novo -> Priori = valor;
        inserePeriod(p,novo);
        return 1;
    }
    else
    {
        printf("\n  [AVISO] A prioridade informada já está cadastrada.\n");
        printf("  > Retornando ao menu anterior...\n");
        return 0;
    }
}

// Functions
void insereLista(Lista *p, No *novo)
{
    p->inicio = auxInsere(p->inicio,novo);
}
int removeLista(Lista *p, int entrada)
{
    int verifica = 0;
    p->inicio = auxRemove(p->inicio,entrada,&verifica);

    return verifica;
}
int imprimeLista(Lista *p,int entrada)
{
    No *aux = p->inicio;

    while(aux!=NULL && aux -> CodSol != entrada)
    {
        aux = aux -> prox;
    }
    if(aux != NULL)
    {
        if(aux -> CodSol == entrada)
        {

            pause();
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║                DADOS DA SOLICITAÇÃO                  ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║                                                      ║\n");
            printf("  ║  Código da solicitação:  %-27d ║\n", aux->CodSol);
            printf("  ║  Código do equipamento:  %-27s ║\n", aux->CodEqu);
            printf("  ║  Nome do equipamento:    %-27s ║\n", aux->NomEqu);
            printf("  ║  Prioridade:             %-27d ║\n", aux->Priori);
            printf("  ║  Período (dias):         %-27d ║\n", aux->Period);
            printf("  ║                                                      ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            return 1;
        }
    }
    return 0;

}
int imprimeSolicita(Lista *p)
{
    No *aux = p->inicio;

    if(aux == NULL)
    {
        printf("\n  [AVISO] Nenhuma solicitação em aberto.\n");
        return 0;
    }

    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════╗\n");
    printf("  ║                                                      ║\n");
    printf("  ║                SOLICITAÇÕES EM ABERTO                ║\n");
    printf("  ║                                                      ║\n");
    printf("  ╠══════════════════════════════════════════════════════╣\n");

    for(int i = 1; aux != NULL; i++, aux = aux->prox)
    {
         printf("  ║    [%02d]  Código: %-35d ║\n", i, aux->CodSol);
    }

    printf("  ╚══════════════════════════════════════════════════════╝\n");

    return 1;
}
int editaLista(Lista *p, int entrada)
{
    int escolha;
    No *aux = p->inicio;

    while(aux != NULL && aux->CodSol != entrada)
    {
        aux = aux->prox;
    }

    if(aux == NULL)
    {
        return 0;
    }
    while(1 == 1)
    {
        do
        {
            escolha = -1;
            pause();
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║                EDIÇÃO DE SOLICITAÇÃO                 ║\n");
            printf("  ║         Selecione o campo que deseja alterar         ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [1]  Alterar prioridade                           ║\n");
            printf("  ║    [2]  Alterar período                              ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [0]  Voltar                                       ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Opção escolhida: ");

            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<0 || escolha >2)
            {
                printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 2.\n");
            }
        }while(escolha<0 || escolha >2);

        pause();

        switch(escolha)
        {
            case 1:
                if(inserePriori(p,aux))
                {
                    printf("\n  [OK] Prioridade editada com sucesso.\n");
                }
                break;

            case 2:
                inserePeriod(p,aux);
                printf("\n  [OK] Período de manutenção editado com sucesso.\n");
                break;

            case 0:
                return 1;
                break;
        }
    }
}
void editaInfo(Lista *p,No *novo)
{
    int escolha, verifica = 0;

    do
    {
        do
        {
            escolha = -1;
            printf("\n");
            printf("  ╔══════════════════════════════════════════════════════╗\n");
            printf("  ║                                                      ║\n");
            printf("  ║             EDITAR DADOS DA SOLICITAÇÃO              ║\n");
            printf("  ║         Selecione o campo que deseja editar          ║\n");
            printf("  ║                                                      ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [1]  Código da solicitação                        ║\n");
            printf("  ║    [2]  Código do equipamento                        ║\n");
            printf("  ║    [3]  Nome do equipamento                          ║\n");
            printf("  ║    [4]  Prioridade da manutenção                     ║\n");
            printf("  ║    [5]  Período de manutenção                        ║\n");
            printf("  ╠══════════════════════════════════════════════════════╣\n");
            printf("  ║    [0]  Retornar                                     ║\n");
            printf("  ╚══════════════════════════════════════════════════════╝\n");
            printf("\n  >> Opção escolhida: ");

            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<0 || escolha>5)
            {
                printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 5.\n");

            }
            pause();
        }while(escolha<0 || escolha>5);

        switch(escolha)
        {
            case 1:
                insereCodSol(p,novo);
                printf("\n  [OK] Código da solicitação editado com sucesso.\n");
                pause();
                break;

            case 2:
                insereCodEqu(p,novo);
                printf("\n  [OK] Código do equipamento editado com sucesso.\n");
                pause();
                break;

            case 3:
                insereNomEqu(p,novo);
                printf("\n  [OK] Nome do equipamento editado com sucesso.\n");
                pause();
                break;

            case 4:
                inserePriori(p,novo);
                printf("\n  [OK] Prioridade editada com sucesso.\n");
                pause();
                break;

            case 5:
                inserePeriod(p,novo);
                printf("\n  [OK] Período de manutenção editado com sucesso.\n");
                pause();
                break;

            case 0:
                verifica = 1;
                break;
        }
    }while(verifica == 0);
}







#endif // LISTLIBR_H_INCLUDED
