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
        novo->prox =aux2;
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

/*No* auxInsere(No* antigo, int valor)
{
    No *novo;
    novo = (No*)malloc(sizeof(No));
    novo->info = valor;
    novo->prox = antigo;
    return novo;
}
No* auxRemove(No* antigo)
{
    if(antigo->prox == NULL)
    {
        free(antigo);
        return NULL;
    }
    No *novo = antigo->prox;
    free(antigo);
    return novo;
}
No* auxInserePos(No *antigo, int valor, int pos)
{
    No *aux = NULL,*aux2 = antigo,*novo;

    novo = (No*)malloc(sizeof(No));
    novo->info=valor;
    novo->prox=NULL;

    for(int cont=1;aux2!=NULL&&cont<pos;cont++)
    {
        aux=aux2;
        aux2=aux2->prox;
    }
    if(aux==NULL)
    {
        novo->prox=aux2;
        return novo;
    }
    aux->prox=novo;
    novo->prox=aux2;
    return antigo;
}
No* auxApagaPos(No *antigo,int pos,int *valor)
{
    No *aux=NULL,*aux2=antigo;
    int cont;

    for(cont=1;aux2!=NULL&&cont<pos;cont++)
    {
        aux=aux2;
        aux2=aux2->prox;
    }

    if(aux2==NULL)
    {
        printf("Posicao inexistente!");
        return antigo;
    }
    if(aux==NULL)
    {
        aux=aux2->prox;
        *valor = aux2->info;
        free(aux2);
        return aux;
    }
    aux->prox=aux2->prox;
    *valor = aux2->info;
    free(aux2);
    return antigo;
}*/

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
void imprimeSolicita(Lista *p)
{
    No *aux = p->inicio;
    if(aux == NULL)
    {
        printf("\nNenhuma solicitação em aberto.");
        pause();
    }
    else
    {
        printf("\nSolicitações em aberto: ");
        for(int i = 1; aux != NULL; i++, aux = aux->prox)
        {
            printf("\n%d - %s",i,aux->CodSol);
        }
    }
}
/*void insereInicioLista(Lista* velho, int valor)
{
    velho->inicio = auxInsere(velho->inicio,valor);
}
void insereQualquerPos(Lista *velho, int pos, int valor)
{
    velho->inicio = auxInserePos(velho->inicio,valor,pos);
}
void insereFimLista(Lista *velho, int valor)
{
    No *aux = velho->inicio;

    if(vaziaLista(velho))
    {
        insereInicioLista(velho,valor);
    }
    else
    {
        while(aux->prox!=NULL)
        {
            aux = aux->prox;
        }
        aux->prox = auxInsere(aux->prox,valor);
    }
}
int apagaInicioLista(Lista *velho)
{
    int valor = 0;

    if(vaziaLista(velho))
    {
        printf("Lista vazia!");
        exit(0);
    }
    else
    {
        valor = velho->inicio->info;
        velho->inicio = auxRemove(velho->inicio);
        return valor;
    }
}
int apagaFimLista(Lista *velho)
{
    No *aux = NULL,*aux2 = velho->inicio;
    int valor;

    if(vaziaLista(velho))
    {
        printf("Lista vazia!");
        exit(0);
    }
    while(aux2->prox!=NULL)
    {
        aux = aux2;
        aux2 = aux2->prox;
    }
    if(aux == NULL)
    {
        valor = velho->inicio->info;
        velho->inicio = auxRemove(aux2);
        return valor;
    }
    valor = aux2->info;
    aux->prox = auxRemove(aux2);
    return valor;
}
int apagaQualquerPosLista(Lista *velho,int pos, int *valor)
{
    if(pos<1 || confereTam(velho->inicio)<pos)
    {
        printf("\nPosição inexistente!");
        return 0;
    }
    if(!vaziaLista(velho))
    {
        velho->inicio=auxApagaPos(velho->inicio,pos,valor);
        return 1;
    }
    printf("lista Vazia!");
    return 0;
}
*/

#endif // LISTLIBR_H_INCLUDED
