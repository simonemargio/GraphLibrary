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

    Grafo G = NULL;
    G=F_alloca_grafo(G);
    G=F_info_grafo(G);
    G=F_crea_grafo(G);
  //  F_stampa_lista_adiacenza(G);
  //  F_stampa_matrice_adiacenza(G);
    system("pause");
    return;
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

    puts("\nDato presente nell'heap");
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

    switch (list_matr)
    {
        case 1: // Lista
            G->tipo_struttura=F_crea_lista_adj;
            break;
        case 2: // Matrice
            G->tipo_struttura=F_crea_matrice_adj;
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
            for(i=0;i<10;i++)
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
    if(Lista!=NULL) newLista->ptrNext=Lista;

    return newLista;
}


void F_stampa_lista_adiacenza(Grafo G)
{
    L Lista=G->struttura;
    puts("\n[Nodo]->[Arco]\n");
    while (Lista!=NULL)
    {
        G->stampa_elemento(Lista->nodo);
        puts("");
        L Arco = Lista;
        while (Arco->ptrArco!=NULL)
        {
            G->stampa_elemento(Arco->ptrArco->nodo);
            Arco=Arco->ptrArco;
        }
         Lista=Lista->ptrNext;
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

