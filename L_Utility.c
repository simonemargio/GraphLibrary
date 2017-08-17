//
// Created by ika on 8/13/2017.
//

#include "L_Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void F_start()
{
    srand((unsigned)time(NULL));
    int menu_principale=-1,scelta=0;
    Grafo G = NULL;
    G=F_alloca_grafo(G);
    G=F_info_grafo(G);
    G=F_crea_grafo(G);
    G->stampa_generale(G);
   // F_stampa_lista_adiacenza(G);
   //  F_stampa_matrice_adiacenza(G);

    do
    {
        scelta=F_menu_principale();
        switch (scelta)
        {
            case 2: // Inserisci un arco
                    F_aggiungi_arco(G);
                    G->stampa_generale(G);
                break;
            case 9:
                scelta=F_menu_avanzato(G->listmatr);
                switch (scelta)
                {
                    case 0:
                        break;
                    default:
                        puts("\nScelta non valida! Ritorno al menu'");
                }
                break;

            case 0:
                menu_principale=0;
                break;
            default:
                puts("\nScelta non valida! Riprovare");
                break;
        }


    }while (menu_principale!=0);



    return;
}

int F_menu_principale()
{
    int scelta = 0;
    puts("\n");
    puts("1] Inserisci un vertice");
    puts("2] Inserisci un arco");
    puts("3] Cancella un vertice");
    puts("4] Cancella un arco");
    puts("5] Calcolo del grafo trasposto");
    puts("6] Esegui visita in ampiezza");
    puts("7] Esegui visina in profondita'");
    puts("8] Stampa il percorso tra due vertici");
    puts("9] Opzioni avanzate");
    puts("");
    puts("0] Esci");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'0','9',-1);

    return scelta;
}

int F_menu_avanzato(int listmatr)
{
    int scelta = 0;
    puts("\n");
    puts("1] Verifica aciclicita' del grafo");
    puts("2] Genera un grafo casuale");
    if(listmatr==1) puts("3] Converti il grafo in una rappresentazione matriciale");
    else    puts("3] Converti il grafo in una rapparesentazione a lista");
    puts("4] Lettura scrittura bla bla");
    puts("");
    puts("0] Torna indietro");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'0','4',-1);

    return scelta;
}

Grafo F_info_grafo(Grafo G)
{
    int list_matr=0, tipo_dato=0, num_elem=0,peso=0;

    list_matr=F_list_matr();        // Scelta se lista adj o matrice
    tipo_dato=F_tipo_dato_grafo();  // Tipo di dato dei nodi
    peso=F_grafo_pesato();
    num_elem=F_num_elem_grafo();    // Numero di elementi

    F_aggiungi_info(G,list_matr,tipo_dato,num_elem,peso); // Gestisce tutte le routine/callback

    return G;
}


int F_grafo_pesato()
{
    int scelta=0;

    puts("Struttura degli archi");
    puts("1] Non pesati");
    puts("2] Pesati");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;

}

int F_list_matr()
{
    int scelta=0;

    puts("Struttura rappresentazione grafo");
    puts("1] Liste di adiacenza");
    puts("2] Matrice di adiacenza");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}


int F_tipo_dato_grafo()
{
    int scelta=0;

    puts("\nDato presente nel grafo");
    puts("1] Interi");
    puts("2] Float");
    puts("3] Caratteri");
    puts("4] Stringhe");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','4',0);

    return scelta;
}

int F_num_elem_grafo()
{
    int scelta=0;

    printf("\nNumero di elementi da inserire:");
    scelta=F_seleziona(2,'0','9',0);

    return scelta;
}

Grafo F_aggiungi_info(Grafo G,int list_matr,int tipo_dato,int num_elem,int peso)
{
    G->nsize=num_elem;
    G->infpeso=peso;
    G->listmatr=list_matr;

    switch (list_matr)
    {
        case 1: // Lista
            G->tipo_struttura=F_crea_lista_adj;
            G->inserisci_arco=F_aggiungi_arco_lista;
            G->seleziona_nodo=F_seleziona_nodo_lista;
            G->stampa_generale=F_stampa_lista_adiacenza;
            break;
        case 2: // Matrice
            G->tipo_struttura=F_crea_matrice_adj;
            G->inserisci_arco=F_aggiungi_arco_matrice;
            G->seleziona_nodo=F_seleziona_nodo_matrice;
            G->stampa_generale=F_stampa_matrice_adiacenza;
            break;
        default:
            puts("Error: selezione tipologia di struttura non valida!\n");
            exit(-1);
    }

    switch (tipo_dato)
    {
        case 1:
            puts("SCELTO INTERO");
            G->tipo_elemento=F_crea_intero;
            G->stampa_elemento=F_stampa_intero;
            break;

        default:
            puts("Error: selezione elemento non valido!\n");
            exit(-2);
    }

    return G;
}

/* Funzione per la selezione di un valore intero */
int F_seleziona(int dim,char minimo,char massimo,int escludi)
{
    /* Variabili in ingresso:
     *
     * dim: dimensione del vettore che conterrà i valori numerici presi in inmput
     * minimo: valore piu' piccolo che puo' essere preso
     * massimo: valore massimo che puo' essere preso
     * escludi: il valore preso in input non deve essere minore uguale del valore escludi
     * */

    char tmp[dim],c='*';
    int intero_preso=0,i=0,flag=0;
    fflush(stdin);

    do
    {
        while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
        {
            printf("\n%c<-\n\n",c);
            if(c>=minimo && c<=massimo)
            {
                tmp[i]=c;
                i++;
            }

        }
        sscanf(tmp,"%d",&intero_preso);

        if(intero_preso<=escludi)
        {
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';

            i=0;
        }
        else // Valore corretto
            flag=1;

    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

Grafo F_crea_matrice_adj(Grafo G)
{
    M struttura_matrice = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)malloc(G->nsize* sizeof(struct struttura_elemento_array_nodo_matrice));

    int i=0;
    for(i=0;i<G->nsize;i++)
    {
        void *elem=G->tipo_elemento();
        array_nodo_matrice[i].nodo=elem;
        array_nodo_matrice[i].ptrPeso=NULL;
    }
    struttura_matrice->nodo=array_nodo_matrice;

    int **matrice =(int **)malloc(G->nsize* sizeof(int *));
    for(i=0;i<G->nsize;i++)
        matrice[i]=(int *)malloc(G->nsize* sizeof(int *));

    struttura_matrice->matrice=matrice;
    G->struttura=struttura_matrice;
    F_inizializza_matrice(G);

    return G;
}

void F_inizializza_matrice(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    int **matrice=struttura_matrice->matrice;

    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++) {
                matrice[i][j]=0;
        }
    return;
}

void F_stampa_matrice_adiacenza(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    int **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    printf("\n[Indice di selezione]:[nodo]\n");
    for(i=0;i<G->nsize;i++)
    {
       if(i!=0) printf(" [%d]:",i);
        else    printf("[%d]:",i);
        G->stampa_elemento(nodi_matrice[i].nodo);
    }

    puts("\n\nMatrice di riferimento");
    for(i=0;i<G->nsize;i++) {
        if(i!=0) puts("");
        for (j = 0; j < G->nsize; j++) {

            printf("|%d|\t", matrice[i][j]);
        }
    }
    return;
}

Grafo F_crea_lista_adj(Grafo G)
{
   L listaAdj = NULL;
   int i=0;
   for(i=0;i<G->nsize;i++)
     {
       void *elem=G->tipo_elemento();
       listaAdj=F_alloca_elemento_lista(listaAdj, elem);
     }
     G->struttura=listaAdj;

    return G;
}

L F_alloca_elemento_lista(L Lista, void *elem)
{

    L newLista=(struct struttura_grafo_lista_adiacenza *)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
    newLista->ptrNext=NULL;
    newLista->ptrArco=NULL;
    newLista->ptrPeso=NULL;
    newLista->nodo=elem;
    if(Lista!=NULL) newLista->ptrNext = Lista;

    return newLista;
}


void F_stampa_lista_adiacenza(Grafo G)
{
    L Lista=G->struttura;
    int i=0;
    puts("\n[Indice]:[Nodo]->[Arco]\n");
    while (Lista!=NULL)
    {
        printf("[%d]:",i);
        G->stampa_elemento(Lista->nodo);

        L Arco = Lista;
        if(Arco->ptrArco == NULL) puts("");
        else
        {
            Arco=Arco->ptrArco;
            printf("-->");

            while (Arco!=NULL)
            {
                G->stampa_elemento(Arco->nodo);
                Arco=Arco->ptrArco;
                if(Arco!=NULL)  printf("->");
                else puts("");
            }
        }

         Lista=Lista->ptrNext;
        i++;
    }

    return;
}

/* Generazione casuale di un valore intero */
void *F_crea_intero()
{
    void *elemento=malloc(sizeof(int));
    int i=rand();
    memcpy(elemento,&i,sizeof(int));

    return elemento;
}

/* Funzione per la stampa di un intero */
void F_stampa_intero(void *elem)
{
    printf("[%d]",*((int *)elem));

    return;
}


void F_aggiungi_arco_lista(Grafo G,int p,int a)
{
    L lista = G->struttura;
    L elem_lista_a = NULL;
    int i = 0;
    void *elem=F_preleva_elem_lista(lista,a);
    elem_lista_a=F_alloca_elemento_lista(elem_lista_a,elem);

    for(i=0;i<p;i++)
    {
        lista=lista->ptrNext;
    }

    if(lista->ptrArco!=NULL)
    {
        elem_lista_a->ptrArco=lista->ptrArco;
    }
    lista->ptrArco=elem_lista_a;

    if(G->listmatr!=1) // PESATO
    {
       float peso = F_inserisci_float(6);
       P stpeso = F_alloca_struttura_peso(peso);
       lista->ptrPeso=stpeso;
    }

    return;
}

P F_alloca_struttura_peso(float peso)
{
    P new_elem = (struct struttura_grafo_pesato *)malloc(sizeof(struct struttura_grafo_pesato));
    new_elem->peso=peso;

    return new_elem;
}

void * F_preleva_elem_lista(L lista,int elemento)
{
    int i=0;

    for(i=0;i<elemento;i++)
    {
        lista=lista->ptrNext;
    }
    void * elem=lista->nodo;

    return elem;
}

void F_aggiungi_arco_matrice(Grafo G,int p,int a)
{
    M matrice = G->struttura;

    matrice->matrice[p][a]=1;

    // controllo se serve il peso

    return;
}



int F_seleziona_nodo_lista(Grafo G)
{
    printf("\nInserisci l'indice dell'elemento che vuoi selezionare:");
    int indice = F_seleziona_indice(5,G->nsize);


    return indice;
}

int F_seleziona_nodo_matrice(Grafo G)
{
    printf("\nInserisci l'indice dell'elemento che vuoi selezionare:");
    int indice = F_seleziona_indice(5,G->nsize);

    return indice;
}

int F_seleziona_indice(int dim, int nsize)
{
    char tmp[dim],c='*';
    int intero_preso=0,i=0,flag=0;
    fflush(stdin);

    do
    {
        while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        sscanf(tmp,"%d",&intero_preso);
        printf("\nIntero: %d\n",intero_preso);
        if(intero_preso<0 && intero_preso > nsize)
        {
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';

            i=0;
        }
        else // Valore corretto
            flag=1;

    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

/* Funzione per l'inserimento da parte dell'utente di un dato float */
float F_inserisci_float(int dim)
{
    /* DICHIARAZIONE VARIABILI */
    char tmp[dim],c='*';
    int i=0;
    float ftemp;

    printf("Aggiunta del peso. Inserire la parte intera:");


    while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
    {
        if(c>='0' && c<='9')
        {
            tmp[i]=c;
            i++;
        }

    }

    tmp[i]='.';
    i++;

    if(i<dim)
    {


        printf("Parte decimale:");

        while( i<dim && (c= (char) getchar()) != '\n' && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        tmp[i]='\0';
    }


    sscanf(tmp,"%f",&ftemp);

    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&ftemp,sizeof(float));
    return ftemp;
}