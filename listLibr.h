#ifndef LISTLIBR_H_INCLUDED
#define LISTLIBR_H_INCLUDED
#include<locale.h>

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
No *insereListaCrescente(Lista *p, No *novo)
{
    No *aux = NULL;
    No *aux2 = p->inicio;
    No *antigo = p->inicio;


    if(novo -> Priori < aux2 -> Priori)
    {
        novo-> prox = antigo;
        return novo;
    }
    if(novo -> Priori == aux2 -> Priori && novo -> Period == aux2 -> Period)
    {
        if(novo -> CodSol < aux2 -> CodSol) // Ver string de CodSol
        {
            novo-> prox = antigo;
            return novo;
        }
        novo -> prox = aux2 -> prox;
        aux2 -> prox = novo;
        return antigo;
    }
    aux = aux2;
    aux2 = aux -> prox;

    while(aux2 -> prox != NULL)
    {
        if(novo -> Priori > aux -> Priori)
        {
            aux = aux2;
            aux2 = aux2 -> prox;
        }
        else
        {
            if(novo -> Period == aux -> Period)
            {
                 if(novo -> CodSol > aux -> CodSol)
                 {
                    novo -> prox = aux -> prox;
                    aux -> prox = novo;
                    return antigo;
                 }
                 aux -> prox = novo;
                 novo -> prox = aux2;
                 return antigo;
            }
            if(novo -> Period < aux -> Period)
            {
                novo -> prox = aux -> prox;
                aux -> prox = novo;
                return antigo;
            }
            novo -> prox = aux2 -> prox;
            aux2 ->prox = novo;
            return antigo;
        }
    }
    aux2 -> prox = novo;
    return antigo;
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
    do
    {
        printf("\n\t\t\tcodigo de solicitação: ");
        scanf("%d",&novo->CodSol);
        limpar_buffer();

        if(novo -> CodSol < 1000 || novo -> CodSol > 9999)
        {
            printf("\n\t\t\tDigite um código de 4 digitos.");
            pause();
        }
        else
        {
            if(VerCod(p,novo -> CodSol))
            {
                printf("\n\t\t\tCodigo de solicitação já cadastrado.");
                pause();
            }
        }
    }while(novo -> CodSol < 1000 || novo -> CodSol > 9999);

}
void insereCodEqu(Lista *p, No *novo)
{
    char entrada[100];
    do
    {
        printf("\n\t\t\tDigite o Código do Equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) != 7)
        {
            printf("\n\t\t\tDigite 6 caracteres!\n");
            pause();
        }
    }while(strlen(entrada) != 7);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo->CodEqu, entrada);
}
void insereNomEqu(Lista *p,No *novo)
{
    char entrada[100];
    do
    {
        printf("\n\t\t\tDigite o Nome do equipamento: ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 21)
        {
            printf("\n\t\t\tDigite no maximo 20 caracteres!\n");
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
                    printf("\n\t\t\tDigite o novo Periodo de prioridade 1 (1 a 7 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 7)
                    {
                        printf("\n\t\t\tPeriodo incorreto (1 a 7 dias).");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 7);
                break;

            case 2:
                do
                {
                    printf("\n\t\t\tDigite o novo periodo de prioridade 2 (1 a 15 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 15)
                    {
                        printf("\n\t\t\tPeriodo incorreto (1 a 15 dias).");
                        pause();
                    }
                }while(novo -> Period < 1 || novo -> Period > 15);
                break;

            case 3:
                do
                {
                    printf("\n\t\t\tDigite o novo periodo de prioridade 3 (1 a 20 dias): ");
                    scanf("%d",&novo->Period);
                    limpar_buffer();

                    if(novo -> Period < 1 || novo -> Period > 20)
                    {
                        printf("\n\t\t\tPeriodo incorreto (1 a 20 dias).");
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
        printf("\n\t\t\tDigite a prioridade de manutenção: ");
        scanf("%d",&valor);
        limpar_buffer();

        if(valor < 1 || valor > 3)
        {
            printf("\n\t\t\tPrioridade inexistente. Digite um valor entre 1 e 3.");
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
        printf("\n\t\t\tPrioridade inserida é a mesma da prioridade cadastrada, retornando.");
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
        printf("\n\t\t\tNenhuma solicitação em aberto.");
        return 0;
    }
    printf("\n\t\t\tSolicitações em aberto: ");
    for(int i = 1; aux != NULL; i++, aux = aux->prox)
    {
        printf("\n%d - %s",i,aux->CodSol);
    }
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
            printf("\n------------Qual deseja alterar?------------");
            printf("\n\n1- Prioridade");
            printf("\n2- Periodo");
            printf("\n0- Sair");
            printf("\n\n------------------------------------------");
            printf("\nOpção escolhida: ");
            scanf("%d",&escolha);
            limpar_buffer();

            if(escolha<0 || escolha >2)
            {
                printf("\n\t\t\t--Escolha inválida--");
                pause();
            }
        }while(escolha<0 || escolha >2);

        switch(escolha)
        {
            case 1:
                inserePriori(p,aux);
                printf("\n\t\t\tPrioridade editada.");
                pause();
                break;
            case 2:
                inserePeriod(p,aux);
                printf("\n\t\t\tPeriodo de manutenção editado.");
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
            limpar_buffer();

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
                printf("\n\t\t\tCodigo de solicitação editado.");
                pause();
                break;

            case 2:
                insereCodEqu(p,novo);
                printf("\n\t\t\tCódigo de equipamento editado.");
                pause();
                break;

            case 3:
                insereNomEqu(p,novo);
                printf("\n\t\t\tNome do equipamento editado.");
                pause();
                break;

            case 4:
                inserePriori(p,novo);
                printf("\n\t\t\tPrioridade editada.");
                pause();
                break;

            case 5:
                inserePeriod(p,novo);
                printf("\n\t\t\tPeriodo de manutenção editado.");
                pause();
                break;

            case 0:
                verifica = 1;
                break;
        }
    }while(verifica == 0);
}







#endif // LISTLIBR_H_INCLUDED
