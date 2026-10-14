#ifndef LISTLIBR_H_INCLUDED
#define LISTLIBR_H_INCLUDED

// STRUCT'S
typedef struct no
{
        char CodSol[100];
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
No *auxInsere(No *antigo,No *novo)
{
    No *aux = NULL,*aux2 = antigo;

    while(aux2!=NULL && aux2->CodSol<novo->CodSol)
    {
        aux = aux2;
        aux2 = aux2->prox;
    }
    if(aux == NULL)
    {
        novo->prox = aux2;
        return novo;
    }
    aux->prox = novo;
    novo->prox = aux2;
    return antigo;
}
No *auxRemove(No *antigo, char entrada[],int *verifica)
{
    No *novo = NULL,*aux = antigo;
    while(aux != NULL && strcmp(aux->CodSol,entrada) != 0)
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
        if(strcmp(aux->CodSol,entrada) == 0)
           {
               novo -> prox = aux -> prox;
               free(aux);
               *verifica = 1;
               return antigo;
           }
    }
    return antigo;
}
int VerCod(Lista *p, char n[])
{
    No *aux = p->inicio;

    while(aux != NULL)
    {
        if( strcmp(aux->CodSol,n) == 0)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

//Inserir infos
void insereCodSol(Lista *p, No *novo)
{
    char entrada[100];
    do
    {
        printf("\ncodigo de solicitação: ");
        fgets(entrada,sizeof(entrada),stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if(strlen(entrada) != 4)
        {
            printf("\nDigite um código de 4 digitos.");
            pause();
        }
        else
        {
            if(VerCod(p,entrada))
            {
                printf("\nCodigo de solicitação já cadastrado.");
                pause();
            }
        }
    }while(VerCod(p,entrada) || strlen(entrada) != 4);

    strcpy(novo->CodSol, entrada);
}
void insereCodEqu(Lista *p, No *novo)
{
    char entrada[100];
    do
    {
        printf("\nDigite o Código do Equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 7)
        {
            printf("\nDigite no maximo 6 caracteres!\n");
            pause();
        }
    }while(strlen(entrada) > 7);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->CodEqu, entrada);
}
void insereNomEqu(Lista *p,No *novo)
{
    char entrada[100];
    do
    {
        printf("\nDigite o Nome do equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 21)
        {
            printf("\nDigite no maximo 20 caracteres!\n");
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
                    printf("\nDigite o novo Periodo de prioridade 1 (1 a 7 dias): ");
                    scanf("%d",&novo->Period);
                    getchar();

                    if(novo -> Period < 1 || novo -> Period > 7)
                    {
                        printf("\nPeriodo incorreto (1 a 7 dias).");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 7);
                break;

            case 2:
                do
                {
                    printf("\nDigite o novo periodo de prioridade 2 (1 a 15 dias): ");
                    scanf("%d",&novo->Period);
                    getchar();

                    if(novo -> Period < 1 || novo -> Period > 15)
                    {
                        printf("\nPeriodo incorreto (1 a 15 dias).");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 15);
                break;

            case 3:
                do
                {
                    printf("\nDigite o novo periodo de prioridade 3 (1 a 20 dias): ");
                    scanf("%d",&novo->Period);
                    getchar();

                    if(novo -> Period < 1 || novo -> Period > 20)
                    {
                        printf("\nPeriodo incorreto (1 a 20 dias).");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 20);
                break;
        }
}
void inserePriori(Lista *p, No *novo)
{
    int valor;
    do
    {
        printf("\nDigite a prioridade de manutenção: ");
        scanf("%d",&valor);
        getchar();

        if(valor < 1 || valor > 3)
        {
            printf("\nPrioridade inexistente. Digite um valor entre 1 e 3.");
            pause();
        }
    }while(valor < 1 || valor > 3);

    if(valor != novo -> Priori)
    {
        novo -> Priori = valor;
        inserePeriod(p,novo);

    }
    else
    {
        printf("\nPrioridade inserida é a mesma da prioridade cadastrada, retornando.");
    }
}

// Functions
void insereLista(Lista *p, No *novo)
{
    p->inicio = auxInsere(p->inicio,novo);
}
int removeLista(Lista *p, char entrada[])
{
    int verifica = 0;
    p->inicio = auxRemove(p->inicio,entrada,&verifica);

    return verifica;
}
int imprimeLista(Lista *p,char entrada[])
{
    No *aux = p->inicio;

    while(aux!=NULL && strcmp(aux -> CodSol,entrada) != 0)
    {
        aux = aux -> prox;
    }
    if(aux != NULL)
    {
        if(strcmp(aux -> CodSol,entrada) == 0)
        {
            printf("----------solicitação----------\n\n");
            printf("Código da solicitação: %s\n", aux->CodSol);
            printf("Código do equipamento:   %s\n", aux->CodEqu);
            printf("Nome do equipamento:      %s\n", aux->NomEqu);
            printf("Prioridade:               %d\n", aux->Priori);
            printf("Periodo de manutenção:  %d dias\n\n", aux->Period);
            printf("--------------------------------");
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
        printf("\nNenhuma solicitação em aberto.");
        return 0;
    }
    printf("\nSolicitações em aberto: ");
    for(int i = 1; aux != NULL; i++, aux = aux->prox)
    {
        printf("\n%d - %s",i,aux->CodSol);
    }
    return 1;
}
int editaLista(Lista *p, char entrada[])
{
    int escolha;
    No *aux = p->inicio;

    while(aux != NULL && strcmp(aux->CodSol,entrada) != 0)
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
            printf("\n------------Qual deseja alterar?------------");
            printf("\n\n1- Prioridade");
            printf("\n2- Periodo");
            printf("\n0- Sair");
            printf("\n\n------------------------------------------");
            printf("\nOpção escolhida: ");
            scanf("%d",&escolha);
            getchar();

            if(escolha<0 || escolha >2)
            {
                printf("\n--Escolha inválida--");
                pause();
            }
        }while(escolha<0 || escolha >2);

        switch(escolha)
        {
            case 1:
                inserePriori(p,aux);
                printf("\nPrioridade editada.");
                pause();
                break;
            case 2:
                inserePeriod(p,aux);
                printf("\nPeriodo de manutenção editado.");
                pause();
                break;
            case 0:
                pause();
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
            printf("\nQual valor deseja editar?");
            printf("\n\n1- Código de solicitação");
            printf("\n2- Código do equipamento");
            printf("\n3- Nome do equipamento");
            printf("\n4- Prioridade da manutenção");
            printf("\n5- Periodo de manutenção");
            printf("\n0- Retornar");
            printf("\n\nResposta: ");
            scanf("%d",&escolha);
            getchar();

            if(escolha<0 && escolha>5)
            {
                printf("\n--Escolha inválida--");

            }
            pause();
        }while(escolha<0 && escolha>5);

        switch(escolha)
        {
            case 1:
                insereCodSol(p,novo);
                printf("\nCodigo de solicitação editado.");
                pause();
                break;

            case 2:
                insereCodEqu(p,novo);
                printf("\nCódigo de equipamento editado.");
                pause();
                break;

            case 3:
                insereNomEqu(p,novo);
                printf("\nNome do equipamento editado.");
                pause();
                break;

            case 4:
                inserePriori(p,novo);
                printf("\nPrioridade editada.");
                pause();
                break;

            case 5:
                inserePeriod(p,novo);
                printf("\nPeriodo de manutenção editado.");
                pause();
                break;

            case 0:
                verifica = 1;
                break;
        }
    }while(verifica == 0);
}
void listaCrescente(Lista *p, Lista *pAux)
{
    No *aux = p -> inicio;
    No *aux2 = pAux -> inicio;

    No *novo = (No*)malloc(sizeof(No));

    strcpy(novo -> CodSol, aux -> CodSol);
    strcpy(novo -> CodEqu, aux -> CodEqu);
    strcpy(novo -> NomEqu, aux -> NomEqu);
    novo -> Priori = aux -> Priori;
    novo -> Period = aux -> Period;
    novo -> prox = NULL;

    insereLista(pAux,novo);
    aux = aux -> prox;
    while(aux != NULL)
    {
        insereListaCrescente()
    }
}
#endif // LISTLIBR_H_INCLUDED
