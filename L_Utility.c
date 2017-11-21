//
// Created by ika on 8/13/2017.
//

#include "L_Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "L_Stack.h"
#include "L_Utility.h"
#include "L_Grafo.h"


void F_start()
{
    srand((unsigned)time(NULL));
    int menu_principale=-1,scelta=0;
    Grafo G = NULL;
    G=F_alloca_grafo(G);
    G=F_info_grafo(G);
    G=F_crea_grafo(G);
    G->stampa_generale(G);

    do
    {
        scelta=F_menu_principale();
        switch (scelta)
        {
            case 1: // Inserisci vertice
                    F_aggiungi_vertice(G);
                break;

            case 2: // Inserisci arco
                    F_aggiungi_arco(G);
                break;

            case 3: // Cancella vertice
                    F_cancella_vertice(G);
                break;

            case 4: // Cancella arco
                    F_cancella_arco(G);
                break;

            case 5: // Grafo trasposto
                    F_grafo_trasposto(G);
                break;
            case 6: // Visita in ampiezza
                    F_visita_ampiezza(G);
                break;
            case 8: // Percorso tra due vertici
                    F_stampa_percorso(G);
                break;
            case 9:
                scelta=F_menu_avanzato(G->listmatr);
                switch (scelta)
                {
                    case 2: // Grafo casuale
                            F_grafo_casuale(G);
                        break;
                    case 3: // Converti grafo
                        F_converti_grafo(G);
                        break;
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

      if(menu_principale!=0)  G->stampa_generale(G);
    }while (menu_principale!=0);
    system("pause");
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

int F_scelta_grafo_casuale()
{
    int scelta=0;

    puts("\nGenerazione di un grafo casuale, preferisci:");
    puts("1] Generare un grafo specificando il tipo");
    puts("2] Generare in maniera totalmente random un grafo");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}

int F_scelta_visita_grafo()
{
    int scelta=0;

    puts("\nSeleziona il tipo di visita che vuoi effettuare:");
    puts("1] Visita in ampiezza (BFS)");
    puts("2] Visita in profondita' (DFS)");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}

Grafo F_aggiungi_info(Grafo G,int list_matr,int tipo_dato,int num_elem,int peso)
{
    G->nsize=num_elem;
    G->infpeso=peso;
    G->listmatr=list_matr;
    G->tipodato=tipo_dato;
    G->pred=NULL;

    switch (list_matr)
    {
        case 1: // Lista
            G->tipo_struttura=F_crea_lista_adj;
            G->inserisci_arco=F_aggiungi_arco_lista;
            G->seleziona_nodo=F_seleziona_nodo_lista;
            G->stampa_generale=F_stampa_lista_adiacenza;
            G->check_nodo_uguale=F_check_nodo_uguale_lista;
            G->inserisci_nodo=F_inserisci_nodo_lista;
            G->cancella_arco=F_cancella_arco_lista;
            G->cancella_nodo=F_cancella_nodo_lista;
            G->grafo_trasposto=F_trasposto_lista;
            G->dealloca_grafo=F_dealloca_grafo_lista;
            G->converti_grafo=F_lista_a_matrice;
            G->inizializza_bfs=F_inizializza_bfs_lista;
            G->vertice_adiacente=F_vertice_adiacente_lista;
            G->check_color=F_controllo_colore_bfs_lista;
            G->change_color=F_cambia_colore_bfs_lista;
            G->stampa_bfs=F_stampa_bfs_lista;
            G->predecessore_bfs=F_predecessoreBfs_lista;
            G->preleva_nodo=F_preleva_nodo_lista;
            G->indice_nodo=F_trova_indice_elem_lista;
            break;
        case 2: // Matrice
            G->tipo_struttura=F_crea_matrice_adj;
            G->inserisci_arco=F_aggiungi_arco_matrice;
            G->seleziona_nodo=F_seleziona_nodo_matrice;
            G->stampa_generale=F_stampa_matrice_adiacenza;
            G->check_nodo_uguale=F_check_nodo_uguale_matrice;
            G->inserisci_nodo=F_inserisci_nodo_matrice;
            G->cancella_arco=F_cancella_arco_matrice;
            G->cancella_nodo=F_cancella_nodo_matrice;
            G->grafo_trasposto=F_trasposto_matrice;
            G->dealloca_grafo=F_dealloca_grafo_matrice;
            G->converti_grafo=F_matrice_a_lista;
            G->inizializza_bfs=F_inizializza_bfs_matrice;
            G->vertice_adiacente=F_vertice_adiacente_matrice;
            G->check_color=F_controllo_colore_bfs_matrice;
            G->change_color=F_cambia_colore_bfs_matrice;
            G->stampa_bfs=F_stampa_bfs_matrice;
            G->predecessore_bfs=F_predecessoreBfs_matrice;
            G->preleva_nodo=F_preleva_nodo_matrice;
            G->indice_nodo=F_trova_indice_elem_matrice;
            break;
        default:
            puts("Error: selezione tipologia di struttura non valida!\n");
            exit(-1);
    }

    switch (tipo_dato)
    {
        case 1: // Intero
            G->tipo_elemento=F_crea_intero;
            G->stampa_elemento=F_stampa_intero;
            G->inserisci_elemento=F_inserisci_intero;
            G->confronto_elementi=F_confronto_interi;
            G->dealloca_elemento=F_dealloca_intero;
            G->copia_dato=F_copia_dato_intero;
            break;

        case 2: // Float
            G->tipo_elemento=F_crea_float;
            G->stampa_elemento=F_stampa_float;
            G->inserisci_elemento=F_inserisci_float;
            G->confronto_elementi=F_confronto_float;
            G->dealloca_elemento=F_dealloca_float;
            G->copia_dato=F_copia_dato_float;
            break;
        case 3: // Carattere
            G->tipo_elemento=F_crea_carattere;
            G->stampa_elemento=F_stampa_carattere;
            G->inserisci_elemento=F_inserisci_carattere;
            G->confronto_elementi=F_confronto_carattere;
            G->dealloca_elemento=F_dealloca_carattere_stringa;
            G->copia_dato=F_copia_dato_carattere;
            break;
        case 4: // Stringa
            G->tipo_elemento=F_crea_stringa;
            G->stampa_elemento=F_stampa_stringa;
            G->inserisci_elemento=F_inserisci_stringa;
            G->confronto_elementi=F_confronto_stringa;
            G->dealloca_elemento=F_dealloca_carattere_stringa;
            G->copia_dato=F_copia_dato_stringa;
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
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;
    //fflush(stdin);
    //fseek(stdin,0,SEEK_END);

    do
    {
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            printf("\n%c<-\n\n",c);
            if(c>=minimo && c<=massimo)
            {
                tmp[i]=c;
                i++;
            }

        }
        intero_preso = (int) strtol(tmp, &ptr, 10);
        //sscanf(tmp,"%d",&intero_preso);

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
   // printf("\nNumero preso:%d",intero_preso);
    return intero_preso;
}

Grafo F_crea_matrice_adj(Grafo G)
{
    M struttura_matrice = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)malloc(G->nsize* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL;
    int i=0;
    for(i=0;i<G->nsize;i++)
    {
        void *elem=G->tipo_elemento();
        array_nodo_matrice[i].nodo=elem;
     //   array_nodo_matrice[i].ptrPeso=NULL;
    }
    struttura_matrice->nodo=array_nodo_matrice;

    float **matrice =(float **)malloc(G->nsize* sizeof(float *));
    for(i=0;i<G->nsize;i++)
        matrice[i]=(float *)malloc(G->nsize* sizeof(float *));

    struttura_matrice->matrice=matrice;
    G->struttura=struttura_matrice;
    F_inizializza_matrice(G);

    return G;
}

void F_inizializza_matrice(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;

    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++) {
                matrice[i][j]=0;
        }
}

void F_stampa_matrice_adiacenza(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    if(G->infpeso==1) puts("\nStruttura della matrice: [Indice]:[nodo]\n");
    else {
        puts("\nStruttura della matrice: [Indice]:[Nodo]-(Peso)->[Nodo]\n");
        F_stampa_peso_matrice_adiacenza(G);
    }
    printf("Nodi presenti:\n");
    for(i=0;i<G->nsize;i++)
    {
       if(i!=0) printf(" [%d]:",i);
        else    printf("[%d]:",i);
        G->stampa_elemento(nodi_matrice[i].nodo);
    }

    puts("\n\nMatrice di riferimento:");
    for(i=0;i<G->nsize;i++) {
            printf("[%d]:\t",i);
        //if(i!=0) puts("");
        for (j = 0; j < G->nsize; j++) {
            if(matrice[i][j]>0 || matrice[i][j]<0)
               printf("|1|\t");
            else printf("|0|\t");
            // printf("|%f|\t", matrice[i][j]);
        }
        puts("");
    }
    puts("\n");
}

void F_stampa_peso_matrice_adiacenza(Grafo G)
{
    int controllo = 0,i=0,j=0;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    printf("Informazioni sul peso degli archi:");

    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++)
        {
           if(matrice[i][j]>0 || matrice[i][j]<0)
           {
               controllo=1;
               G->stampa_elemento(nodi_matrice[i].nodo);
               printf("-");
               printf("(%f)",matrice[i][j]);
               printf("->");
               G->stampa_elemento(nodi_matrice[j].nodo);
               puts("");
           }
        }
    
    if(controllo!=1) puts(" non sono ancora presenti archi con pesi.\n");
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
    newLista->extra=NULL;
    newLista->nodo=elem;
    if(Lista!=NULL) newLista->ptrNext = Lista;

    return newLista;
}


void F_stampa_lista_adiacenza(Grafo G)
{
    L Lista=G->struttura;
    int i=0;
    if(G->infpeso==1) puts("\nStruttura della lista: \n[Indice]:[Nodo]->[Nodo]\n");
    else
    {
        puts("\nStruttura della lista: \n[Indice]:[Nodo]-(Peso)->[Nodo]\n");
        F_stampa_peso_lista_adiacenza(G);
    }
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

}

void F_stampa_peso_lista_adiacenza(Grafo G)
{
    int controllo = 0;
    L Lista=G->struttura;
    printf("Informazioni sul peso degli archi:");

    while (Lista!=NULL)
    {
        if(Lista->ptrArco!=NULL) {
            puts("");
            controllo = 1;
            G->stampa_elemento(Lista->nodo);
            printf("-");
            printf("(%f)", Lista->ptrArco->ptrPeso->peso);
            printf("->");
            G->stampa_elemento(Lista->ptrArco->nodo);

            L Arco = Lista->ptrArco;

             while (Arco!=NULL && Arco->ptrArco!=NULL)
             {
                 puts("");
                 G->stampa_elemento(Lista->nodo);
                 printf("-");
                 printf("(%f)",Arco->ptrArco->ptrPeso->peso);
                 printf("->");
                 G->stampa_elemento(Arco->ptrArco->nodo);
                 Arco=Arco->ptrArco;
               //  puts("");
             }
        }
        Lista=Lista->ptrNext;
    }

    if(controllo!=1) puts(" non sono ancora presenti archi con pesi.\n");
    puts("\n");
}

/* Generazione casuale di un valore intero */
void *F_crea_intero()
{
    void *elemento=malloc(sizeof(int));
    int i=rand();
    memcpy(elemento,&i,sizeof(int));

    return elemento;
}

int F_random_int_range(int min, int max)
{
    return min + rand() % (max+1 - min);
}


/* Funzione per la stampa di un intero */
void F_stampa_intero(void *elem)
{
    printf("[%d]",*((int *)elem));
}

/* Funzione per la stampa di un elemento float */
void F_stampa_float(void *elem)
{
    printf("[%f]",*((float *)elem));
}


/* Funzione per la stampa di un carattere */
void F_stampa_carattere(void *elem)
{
    printf("[%c]",*((char *)elem));
}

/* Funzione per la stampa di una stringa */
void F_stampa_stringa(void *elem)
{
    printf("[%s]",((char *)elem));
}

/*void F_aggiungi_arco_lista(Grafo G,int p,int a)
{
    L lista = G->struttura;
    L elem_lista_a = NULL;
    int i = 0,checkArco=0;
    void *elem=F_preleva_elem_lista(lista,a);
    elem_lista_a=F_alloca_elemento_lista(elem_lista_a,elem);

    for(i=0;i<p;i++)
    {
        lista=lista->ptrNext;
    }

    if(lista->ptrArco!=NULL)
    {
       if(G->infpeso!=1) {
           L checkArcoPresente = lista;
           while (checkArcoPresente != NULL) {
               if (elem_lista_a->nodo == checkArcoPresente->nodo) {
                   checkArco = F_cambia_peso_lista(checkArcoPresente,G->stampa_elemento);
                   free(elem_lista_a);
                   break;
               }
               checkArcoPresente = checkArcoPresente->ptrArco;
           }
       }
      if(!checkArco) elem_lista_a->ptrArco=lista->ptrArco;
    }

    if(!checkArco) {
        lista->ptrArco = elem_lista_a;

        if (G->infpeso != 1) // PESATO
        {
            float peso = F_inserisci_float(6);
            P stpeso = F_alloca_struttura_peso(peso);
            elem_lista_a->ptrPeso = stpeso;
        }
    }
}*/

void F_aggiungi_arco_lista(Grafo G,int p,int a)
{
    L lista = G->struttura;
    L elem_lista_a = NULL;
    int i = 0,checkArco=0;
    void *elem=F_preleva_elem_lista(lista,a);
    elem_lista_a=F_alloca_elemento_lista(elem_lista_a,elem);

    for(i=0;i<p;i++)
    {
        lista=lista->ptrNext;
    }

    if(lista->ptrArco!=NULL)
    {
       L checkArcoPresente = lista;
       while (checkArcoPresente != NULL)
       {
           if (elem_lista_a->nodo == checkArcoPresente->nodo)
           {
               if(G->infpeso!=1)
               {
                   checkArco = F_cambia_peso_lista(checkArcoPresente,G->stampa_elemento);
                   free(elem_lista_a);
                   break;
               }
               else {puts("\nE' gia' presente un arco con il nodo selezionato!\n"); checkArco=2; break; }
           }
            checkArcoPresente = checkArcoPresente->ptrArco;
       }

        if(!checkArco) elem_lista_a->ptrArco=lista->ptrArco;
    }

    if(!checkArco) {
        lista->ptrArco = elem_lista_a;

        if (G->infpeso != 1) // PESATO
        {
           // float peso = F_inserisci_float(6);
            void *pe=F_inserisci_float(6);
            float peso = *((float *)pe);
            P stpeso = F_alloca_struttura_peso(peso);
            elem_lista_a->ptrPeso = stpeso;
        }
    }
}

int F_cambia_peso_lista(L elem,StampaElemento stampa_elemento)
{
    printf("\nE' gia' presente un arco pesato che arriva al nodo:");
    stampa_elemento(elem->nodo);
    int scelta = F_menu_scelta_cambio_peso();

    if(scelta==1) {// elem->ptrPeso->peso= F_inserisci_float(6);
        void *p=F_inserisci_float(6);
        float peso=*((float *)p);
        elem->ptrPeso->peso=peso;
    }
    else
        puts("");  // Usato per evitare deep indentation

    return 1;
}

int F_menu_scelta_cambio_peso()
{
    int scelta=0;

    puts("\nVuoi cambiare peso?\n");
    puts("1] Si, cambia peso");
    puts("2] No, lascia il peso originale");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
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
    Nm nodi_matrice = matrice->nodo;
    int scelta = 0;

    if(G->infpeso!=1) // PESATO
    {
        if(matrice->matrice[p][a]>0 || matrice->matrice[p][a]<0)
        {
            printf("\nE' gia' presente un arco pesato che arriva al nodo: ");
            G->stampa_elemento(nodi_matrice[a].nodo);
            scelta = F_menu_scelta_cambio_peso();
        }

        if(scelta==1 || matrice->matrice[p][a]==0) {
          //  float peso = F_inserisci_float(6);
            void *pe=F_inserisci_float(6);
            float peso=*((float *)pe);
            matrice->matrice[p][a] = peso;
        }
    }
    else
    matrice->matrice[p][a]=1;
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
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;
    //fflush(stdin);
    for(i=0;i<dim;i++)
        tmp[i]='*';
    i=0;

    do
    {
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            printf("\n%c<-\n\n",c);
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        for(i=0;i<dim;i++)
            printf("<<%c>>",tmp[i]);

        intero_preso = (int) strtol(tmp, &ptr, 10);
       // sscanf(tmp,"%d",&intero_preso);
        printf("\nInteroo: |%d|\n",intero_preso);
        if(intero_preso<0 || intero_preso > nsize)
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

/* Funzione per l'inserimento da parte dell'utente di un dato intero */
void *F_inserisci_intero(int dim)
{
    /* DICHIARAZIONI VARIABILI */
    printf("\n>>%d<<\n",dim);
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0;
    //fflush(stdin);

    for(i=0;i<dim;i++)
        tmp[i]='*';

    printf("\nINTERO: I valori vengono presi in modulo.\nInserire un valore intero di 10 cifre (Max: %d):",INT_MAX);
    i=0;

        while( (c=(char) getchar())!='\n' && i<10 && c!=EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }

    intero_preso = (int) strtol(tmp, &ptr, 10);  // tmp=dove metto str=dovrebbe essere i caratteri sartati in mezzo, 10 è la base

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
   // printf("\nHO PRESO: ||%d||int - ho scartato |%s|\n",intero_preso,ptr);
    return elemento;
}



/* Funzione per l'inserimento da parte dell'utente di un dato float */
/*float F_inserisci_float(int dim)
{

    char tmp[dim],c='*';
    int i=0;
    float ftemp;
   // fflush(stdin);

    printf("Aggiunta del peso.\nVerra' chiesto successivamente se si vuole il valore in negativo!\nInserire la parte intera:");


    while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
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

        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        tmp[i]='\0';
    }


   // sscanf(tmp,"%f",&ftemp);
    ftemp=strtof(tmp,NULL);
    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&ftemp,sizeof(float));
    printf("\nSi vuole esprimere il valore: [%f] in negativo?\n1-Si\n2-No\nSeleziona tramite valore numerico:",ftemp);
    int scelta = F_seleziona(1,'1','2',0);
    if(scelta==1) ftemp=F_ritorna_negativo(ftemp);
    printf("\nOK RITORNO |%f|\n",ftemp);
    return ftemp;
}*/

void *F_inserisci_float(int dim)
{
    /* DICHIARAZIONE VARIABILI */
    char tmp[dim],c='*';
    int i=0;
    float ftemp;
    // fflush(stdin);

    printf("Aggiunta del peso.\nVerra' chiesto successivamente se si vuole il valore in negativo!\nInserire la parte intera:");


    while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
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

        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }
        tmp[i]='\0';
    }


    // sscanf(tmp,"%f",&ftemp);
    ftemp=strtof(tmp,NULL);
    void *elemento=malloc(sizeof(float));

    printf("\nSi vuole esprimere il valore: [%f] in negativo?\n1-Si\n2-No\nSeleziona tramite valore numerico:",ftemp);
    int scelta = F_seleziona(1,'1','2',0);
    if(scelta==1) ftemp=F_ritorna_negativo(ftemp);
    memcpy(elemento,&ftemp,sizeof(float));
    printf("\nOK RITORNO |%f|\n",*((float *)elemento));
    return elemento;
}




float F_ritorna_negativo(float num)
{
    num=(num)*(-1);
    return num;
}

int F_check_nodo_uguale_lista(Grafo G,void *elem)  // 0 non c'è . 1 c'è
{
    int controllo = 0,i=0;
    L lista = G->struttura;

    while (lista!=NULL)
    {
        printf("\n||%d|| ||%d||\n",*((int *)elem),*((int*)lista->nodo));
        i = G->confronto_elementi(lista->nodo,elem);
        if(i==0)
        {
            controllo=1;
            break;
        }

        lista=lista->ptrNext;
    }

    return controllo;
}

int F_check_nodo_uguale_matrice(Grafo G,void *elem)
{
    int i=0,controllo=0,j=0;
    M Matrice = G->struttura;
    Nm nodo_matrice = Matrice->nodo;

    for(i=0;i<G->nsize;i++)
        {
            j = G->confronto_elementi(nodo_matrice[i].nodo,elem);
            if(j==0)
            {
                controllo=1;
                break;
            }
        }

    return controllo;
}

/* Funzione per il confronto di elementi interi */
int F_confronto_interi(void *stringa,void *stringa_nodo)
{
    int controllo=0;

    if(*((int *)stringa) < *((int *)stringa_nodo))
    {
        controllo=-1;
    }
    else
    {
        if(*((int *)stringa) > *((int *)stringa_nodo))
        {
            controllo=1;
        }
        else
            controllo=0;
    }
    return controllo;
}


/* Funzione per il confronto di elementi di tipo carattere */
int F_confronto_carattere(void *stringa,void *stringa_nodo)
{
    int controllo=0;

    if(*((char *)stringa) < *((char *)stringa_nodo))
    {
        controllo=-1;
    }
    else{
        if(*((char *)stringa) > *((char *)stringa_nodo)) {
            controllo=1;
        }
        else
            controllo=0;
    }
    return controllo;
}

/* Funzione per il confronto di elementi float */
int F_confronto_float(void *stringa,void *stringa_nodo)
{
    int controllo=0;
    if(*((float *)stringa) < *((float *)stringa_nodo))
    {
        controllo=-1;
    }
    else
    {
        if(*((float *)stringa) > *((float *)stringa_nodo))
        {
            controllo=1;
        }
        else
            controllo=0;
    }
    return controllo;
}


/* Funzione per il confronto di elementi di tipo stringa */
int F_confronto_stringa(void *stringa,void *stringa_nodo)
{
    int controllo=0;
    int i=strcmp((char*)stringa,(char*)stringa_nodo);

    if(i<0)
    {
        controllo=-1;
    }
    else
    {
        if(i>0)
        {
            controllo=1;
        }
        else
            controllo=0;
    }
    return controllo;
}

void F_inserisci_nodo_lista(Grafo G,void *elem)
{
    L Lista = G->struttura;

    L NewLista = F_alloca_elemento_lista(Lista,elem);

    G->nsize=G->nsize+1;
    G->struttura=NewLista;
}

void F_inserisci_nodo_matrice(Grafo G,void *elem)
{
    int i=0,new_size=(G->nsize+1);
    M struttura_matrice = G->struttura;
    float **matrice_old=struttura_matrice->matrice;

    float **matrice_new=(float **)malloc(new_size* sizeof(float *));
    for(i=0;i<new_size;i++)
          matrice_new[i]=(float *)malloc(new_size* sizeof(float *));

    F_copia_matrice(matrice_new,matrice_old,G->nsize);


    Nm nodi_matrice = struttura_matrice->nodo;
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)realloc(nodi_matrice,new_size* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL;
    array_nodo_matrice[G->nsize].nodo=elem;


    // DEALLOCARE
    for(i=0;i<G->nsize;i++)
        free(matrice_old[i]);

    free(matrice_old);

    G->nsize=new_size;
    struttura_matrice->nodo=array_nodo_matrice;
    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
}


void F_copia_matrice (float ** destmat, float ** srcmat,int dim)
{
   // memcpy(destmat,srcmat, dim*dim*sizeof(float));
    int i=0,j=0;

    for(i=0;i<dim+1;i++)
        for(j=0;j<dim+1;j++)
            destmat[i][j]=0;

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            destmat[i][j] = srcmat[i][j];
}

void F_copia_matrice_identica (float ** destmat, float ** srcmat,int dim)
{
    int i=0,j=0;

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            destmat[i][j]=0;

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            destmat[i][j] = srcmat[i][j];

}

void F_cancella_arco_lista(Grafo G,int p,int a)
{
    L Lista=G->struttura;
    L Nodo_p = Lista;
    L Nodo_a = Lista;
    void *Elem_a=NULL;
    int i=0,c=-1;

    for(i=0;i<p;i++)
        Nodo_p=Nodo_p->ptrNext;

    for(i=0;i<a;i++)
        Nodo_a=Nodo_a->ptrNext;

    Elem_a=Nodo_a->nodo;


    while(Nodo_p!=NULL)
    {
        if(Nodo_p->ptrArco!=NULL) {
            c = G->confronto_elementi(Nodo_p->ptrArco->nodo, Elem_a);

            if (c == 0) // Trovato
            {
                L Tmp = Nodo_p->ptrArco;
                if (Nodo_p->ptrArco->ptrArco != NULL) // C'è qualcosa dopo
                {
                    Nodo_p->ptrArco=Nodo_p->ptrArco->ptrArco;
                } else {
                    Nodo_p->ptrArco = NULL;
                }
                free(Tmp); // Non si deve deallocare l'eleemnto in quando sono puntatori alla struttura principale
                break;
            }
        }
        Nodo_p=Nodo_p->ptrArco;
    }

    if(c!=0) printf("\nNodo non presente!\n");
    else printf("\nDeallocazione effettuata!\n");
}


void F_cancella_arco_matrice(Grafo G,int p,int a)
{
    M matrice = G->struttura;
    matrice->matrice[p][a]=0;
}

void F_dealloca_intero(void *elem)
{
    printf("\n\nDEALLOCO:%d\n\n",*((int *)elem));
    free(((int *)elem));
}

void F_dealloca_carattere_stringa(void *elem)
{
    printf("\n\nDEALLOCO:%c\n\n",*((char *)elem));
    free(((char *)elem));
}

void F_dealloca_float(void *elem)
{
    printf("\n\nDEALLOCO:%f\n\n",*((float *)elem));
    free(((float *)elem));
}

void F_cancella_nodo_matrice(Grafo G,int c)
{
    int new_size=(G->nsize-1),i=0,j=0,ni=0,nj=0;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    float **matrice_old=struttura_matrice->matrice;

    float **matrice_new=(float **)malloc(new_size* sizeof(float *));
    for(i=0;i<new_size;i++)
        matrice_new[i]=(float *)malloc(new_size* sizeof(float *));

    for(i=0;i<G->nsize;i++)
    {
        if(i!=c)
        {
            for(j=0,nj=0;j<G->nsize;j++)
            {
                if(j!=c)
                {
                    matrice_new[ni][nj]=matrice_old[i][j];
                    nj++;
                }
            }
            ni++;
        }
    }

    nodi_matrice[c].nodo=NULL;

    for(i=c;i<new_size;i++)
        nodi_matrice[i]=nodi_matrice[i+1];
    free(matrice_old);
    nodi_matrice = (struct struttura_elemento_array_nodo_matrice *)realloc(nodi_matrice,new_size* sizeof(struct struttura_elemento_array_nodo_matrice));
    nodi_matrice->extra=NULL;
    struttura_matrice->nodo=nodi_matrice;
    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
    G->nsize=new_size;
}

void F_cancella_nodo_lista(Grafo G,int c)
{
    L Lista = G->struttura,curr=NULL,prec=NULL,Lista_del=Lista;

    if(Lista!=NULL) {
        int i=0,confronto;

        for(i=0;i<c;i++)
            Lista_del=Lista_del->ptrNext;

        void *elem_del = Lista_del->nodo;


      L Tmp=Lista;

        while(Tmp!=NULL)
        {
            curr=Tmp->ptrArco, prec=Tmp;

            while(curr!=NULL)
            {
                confronto = G->confronto_elementi(elem_del, curr->nodo);
                if (confronto == 0)
                {
                    if(curr==Tmp->ptrArco) Tmp->ptrArco=curr->ptrArco;
                    else prec->ptrArco=curr->ptrArco;
                    free(curr);
                    break;
                } else{
                    curr=curr->ptrArco;
                    prec=prec->ptrArco;
                }
            }
            Tmp=Tmp->ptrNext;
        }


        if(i==0) // testa
        {
            Tmp=Lista;
            Lista=Lista->ptrNext;
        }
        else
        {
            int s=0;
            L CodaMezz=Lista;
            if(i==(G->nsize-1)) // coda
            {
                for(;s<(G->nsize-2);s++)
                    CodaMezz=CodaMezz->ptrNext;

                Tmp=CodaMezz->ptrNext;
                CodaMezz->ptrNext=NULL;
            } else
            {
                int elmprec=(i-1);
                for(;s<elmprec;s++)
                    CodaMezz=CodaMezz->ptrNext;

                Tmp=CodaMezz->ptrNext;
                CodaMezz->ptrNext=CodaMezz->ptrNext->ptrNext;
            }
        }
        G->dealloca_elemento(Tmp->nodo);
        free(Tmp);

        G->nsize = (G->nsize - 1);
        G->struttura = Lista;

    } else puts("\nStruttura non presente!\n");
}

void F_trasposto_lista(Grafo G)
{
    L Lista_old = G->struttura;
    L Lista_new = NULL;
    L ListaOldPrinc = G->struttura;
    int controllo = 0;
    float InfPeso = 0;

    while (ListaOldPrinc!=NULL)
    {
        void *elem = G->copia_dato(ListaOldPrinc->nodo);
        L newElLista=(struct struttura_grafo_lista_adiacenza *)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        newElLista->ptrNext=NULL;
        newElLista->ptrArco=NULL;
        newElLista->ptrPeso=NULL;
        newElLista->extra=NULL;
        newElLista->nodo=elem;

        if(Lista_new!=NULL)
        {
            L tmp=NULL;
            for(tmp=Lista_new; tmp->ptrNext!=NULL;tmp=tmp->ptrNext);
            tmp->ptrNext=newElLista;

        }else Lista_new=newElLista;

        ListaOldPrinc=ListaOldPrinc->ptrNext;
    }

    ListaOldPrinc=G->struttura;
    L ListaNewPrinc=Lista_new;

    while(ListaOldPrinc!=NULL)
    {
        L ArcoOld = ListaOldPrinc->ptrArco;
       // printf("\nOLD - Considero l'elemento (%d)\n",*((int *)ListaOldPrinc->nodo));

        while (ArcoOld!=NULL)
        {
         //   printf("\nOLD - L'elemento di prima ha un arco (%d), lo cerco nella lista nuova",*((int *)ArcoOld->nodo));
            if(G->infpeso!=1) InfPeso=ArcoOld->ptrPeso->peso;

            while(ListaNewPrinc!=NULL)
            {
           //     printf("\nConfronto il nodo vecchio (%d) con quello nuovo che in questo momento e' (%d)\n",*((int *)ArcoOld->nodo),*((int *)ListaNewPrinc->nodo));
                controllo=G->confronto_elementi(ArcoOld->nodo,ListaNewPrinc->nodo);
                if(controllo==0) break;
                ListaNewPrinc=ListaNewPrinc->ptrNext;
            }
            L ListaNewPartenza=NULL;
            if(ListaNewPrinc!=NULL)
            {
               ListaNewPartenza=ListaNewPrinc;
             //  printf("\nNEW - Ho trovato l'elemento nella nuova lista (%d). Questo sara' l'elemento di partenza",*((int *)ListaNewPartenza->nodo));
               ListaNewPrinc=Lista_new;
            }
            else{puts("\nERROR: arco grafo trasposto"); exit(-4);}

            void *ArrivoOld = ListaOldPrinc->nodo;
           // printf("\nOLD - L'elelemtno che diventerà il nuovo arco sara' (%d), lo cerco nella nuova lista",*((int *)ListaOldPrinc->nodo));
            while(ListaNewPrinc!=NULL)
            {
                controllo=G->confronto_elementi(ArrivoOld,ListaNewPrinc->nodo);
             //   printf("\nConfronto l'elemento vecchio (%d) con quello nuovo che sto cercando nelle lista che ora e' (%d)",*((int *)ArrivoOld),*((int *)ListaNewPrinc->nodo));
                if(controllo==0) break;
                ListaNewPrinc=ListaNewPrinc->ptrNext;
            }

            if(ListaNewPrinc!=NULL)
            {
                void *ArrivoNew=ListaNewPrinc->nodo;
                L ArcoNew = NULL;
                ArcoNew = F_alloca_elemento_lista(ArcoNew,ArrivoNew);

                if(G->infpeso!=1)
                {
                    P PesoNew=F_alloca_struttura_peso(InfPeso);
                    ArcoNew->ptrPeso=PesoNew;
                }

                if(ListaNewPartenza->ptrArco!=NULL)
                {
                    ArcoNew->ptrArco=ListaNewPartenza->ptrArco;
                    ListaNewPartenza->ptrArco=ArcoNew;
                }else ListaNewPartenza->ptrArco=ArcoNew;

            }else{puts("\nERROR: arco grafo trasposto!\n"); exit(-5);}

            ListaNewPrinc=Lista_new;
            ArcoOld=ArcoOld->ptrArco;
        }

        ListaOldPrinc=ListaOldPrinc->ptrNext;
    }

    F_dealloca_grafo_lista(Lista_old,G);
    G->struttura=Lista_new;
}

void F_dealloca_grafo_lista(void *struttura,Grafo G)
{
    L Lista = struttura;
    L TmpNext=NULL;
    L ListaPrinc=Lista;
    while(Lista!=NULL)
    {
        L Arco = Lista->ptrArco;

        while (Arco!=NULL)
        {
            if(G->infpeso!=1)
            {
                Arco->ptrPeso->peso=0;
                free(Arco->ptrPeso);
            }

            TmpNext=Arco->ptrArco;
            Arco->ptrArco=NULL;

            Arco=TmpNext;
        }
        Lista=TmpNext;
    }

    while (ListaPrinc!=NULL)
    {
        TmpNext=ListaPrinc->ptrNext;
        G->dealloca_elemento(ListaPrinc->nodo);
        ListaPrinc=TmpNext;
    }

    puts("\nHo deallocato la lista precedente!\n");
}

void F_dealloca_grafo_matrice(void *struttura,Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    for (i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++)
            matrice[i][j]=0;
    for(i=0;i<G->nsize;i++)
        G->dealloca_elemento(nodi_matrice[i].nodo);
    puts("\nHo deallocato la matrice precedente!\n");
}

void F_trasposto_matrice(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    float **matrice_old=struttura_matrice->matrice;

    float **matrice_new=(float **)malloc(G->nsize* sizeof(float *));
    for(i=0;i<G->nsize;i++)
        matrice_new[i]=(float *)malloc(G->nsize* sizeof(float *));

    F_copia_matrice_identica(matrice_new,matrice_old,G->nsize);

    F_inizializza_matrice(G);

    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++)
        {
            if(matrice_new[i][j] < 0 || matrice_new[i][j] > 0)
                matrice_old[j][i]=matrice_new[i][j];
        }

    for(i=0;i<G->nsize;i++)
        free(matrice_new[i]);

    free(matrice_new);
}


/* Funzione per la copia di un tipo intero */
void *F_copia_dato_intero(void *val)
{
    int *intero=malloc(sizeof(int));
    memcpy(intero,((int *)val),sizeof(int)) ;

    return intero;
}

/* Funzione per la copia di un tipo carattere */
void *F_copia_dato_carattere(void *val)
{
    char *carattere=malloc(sizeof(char));
    memcpy(carattere,((char *)val),sizeof(char)) ;

    return carattere;
}

/* Funzione per la copia di un tipo float */
void *F_copia_dato_float(void *val)
{
    float *fl=malloc(sizeof(float));
    memcpy(fl,((float *)val),sizeof(float)) ;

    return fl;
}

/* Funzione per la copia di un tipo stringa */
void *F_copia_dato_stringa(void *val)
{
    int l=strlen(((char *)val));
    char *stringa=malloc(l*sizeof(char));
    strcpy(stringa,val);

    return stringa;
}


void F_matrice_a_lista(Grafo G)
{
    int i=0,j=0,k=0;
    L Lista_new=NULL;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    for(i=0;i<G->nsize;i++)
    {
        void *elem=G->copia_dato(nodi_matrice[i].nodo);
        G->dealloca_elemento(nodi_matrice[i].nodo);
        L newElLista=(struct struttura_grafo_lista_adiacenza *)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        newElLista->ptrNext=NULL;
        newElLista->ptrArco=NULL;
        newElLista->ptrPeso=NULL;
        newElLista->extra=NULL;
        newElLista->nodo=elem;

        if(Lista_new!=NULL)
        {
            L tmp=NULL;
            for(tmp=Lista_new; tmp->ptrNext!=NULL;tmp=tmp->ptrNext);
            tmp->ptrNext=newElLista;

        }else Lista_new=newElLista;
    }
    L ListaRiga = Lista_new;
    L ListaColonna = Lista_new;

    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++)
        {
            if(matrice[i][j]>0 || matrice[i][j]<0)
            {
                for(k=0;k<i;k++)
                    ListaRiga=ListaRiga->ptrNext;

                for(k=0;k<j;k++)
                    ListaColonna=ListaColonna->ptrNext;

                if(ListaRiga==NULL || ListaColonna==NULL) {puts("\nError: conversione matrice a lista!"); exit(-10);}
                L newElLista = NULL;
                newElLista=F_alloca_elemento_lista(newElLista,ListaColonna->nodo);

                if(G->infpeso!=1)
                {
                   P newPeso=F_alloca_struttura_peso(matrice[i][j]);
                   newElLista->ptrPeso=newPeso;
                }

                if(ListaRiga->ptrArco!=NULL)
                {
                    newElLista->ptrArco=ListaRiga->ptrArco;
                    ListaRiga->ptrArco=newElLista;
                }else ListaRiga->ptrArco=newElLista;
                ListaRiga=Lista_new; ListaColonna=Lista_new;
            }
        }

    G=F_aggiungi_info(G,1,G->tipodato,G->nsize,G->infpeso);
    G->struttura=Lista_new;
}

void F_lista_a_matrice(Grafo G)
{
    int i=0,j=0,controllo=-1;
    L Lista=G->struttura;
    L ListaScorr=Lista;

    M struttura_matrice = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)malloc(G->nsize* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL;
    float **matrice_new=(float **)malloc(G->nsize* sizeof(float *));
    for(i=0;i<G->nsize;i++)
        matrice_new[i]=(float *)malloc(G->nsize* sizeof(float *));

    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
    F_inizializza_matrice(G);

    for(i=0;i<G->nsize;i++)
    {
        void *newEl=F_copia_dato_intero(ListaScorr->nodo);
        array_nodo_matrice[i].nodo=newEl;
        ListaScorr=ListaScorr->ptrNext;
    }
    struttura_matrice->nodo=array_nodo_matrice;
    ListaScorr=Lista;

    for(i=0;i<G->nsize;i++) {
        L Arco = ListaScorr->ptrArco;

        while (Arco != NULL) {

            L Colonna=Lista;

            for(j=0;Colonna!=NULL;j++,Colonna=Colonna->ptrNext)
            {
                controllo=G->confronto_elementi(Colonna->nodo,Arco->nodo);
                if(controllo==0) break;
            }

            if(Colonna==NULL) {puts("\nError: funzione lista to matrice!"); exit(-1);}

            if(G->infpeso!=1)
            {
                float peso=Arco->ptrPeso->peso;
                matrice_new[i][j]=peso;
            }else
                matrice_new[i][j]=1;

            Arco = Arco->ptrArco;
        }
        ListaScorr=ListaScorr->ptrNext;
    }
    F_dealloca_grafo_lista(Lista,G);
    G=F_aggiungi_info(G,2,G->tipodato,G->nsize,G->infpeso);
}

void *F_inizializza_bfs_lista(Grafo G,int s)
{
    L Nodo_s=NULL;
    int cont=0;
    L Lista=G->struttura;

    while(Lista!=NULL)
    {
        C newColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));

        if(cont==s) {
            newColore->colore=1;
            Nodo_s=Lista;
        }
        else newColore->colore=0;

        Lista->extra=newColore;
        Lista=Lista->ptrNext;
        cont++;
    }

    return Nodo_s;
}

void *F_inizializza_bfs_matrice(Grafo G,int s)
{
    Nm Nodo_s=NULL;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,j=0;

    for(i=0;i<G->nsize;i++)
    {
        C newColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));

        if(i==s)
        {
            newColore->colore=1;
            Nodo_s=nodi_matrice[i].nodo;
        } else newColore->colore=0;

        nodi_matrice[i].extra=newColore;
    }

    return Nodo_s;
}

void *F_vertice_adiacente_lista(Grafo G,void *u, void *ultimo)
{
    int controllo=-1;
    L Nodo=u;
    L Ulti=ultimo;
    L Lista=G->struttura;

    while (Lista!=NULL)
    {
        controllo=G->confronto_elementi(Lista->nodo,Nodo->nodo);
        if(controllo==0) break;
        Lista=Lista->ptrNext;
    }
    Nodo=Lista;

    if(Nodo->ptrArco!=NULL) {

        if (ultimo != NULL) {

            while (Nodo!=NULL) {

                controllo = G->confronto_elementi(Nodo->nodo, Ulti->nodo);
                if(controllo==0) {
                    if(Nodo->ptrArco!=NULL) ultimo=Nodo->ptrArco;
                    else ultimo=NULL;
                    break;
                }

                Nodo=Nodo->ptrArco;
            }

        } else ultimo=Nodo->ptrArco;
    }

    return ultimo;
}

void *F_vertice_adiacente_matrice(Grafo G,void *u, void *ultimo)
{
    Nm Nodo=u;
    Nm Ulti=ultimo;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0, j=0,salvaNodo=-1,confronto=-1;

    for(i=0;i<G->nsize;i++) // Seleziono la riga i
    {
        confronto=G->confronto_elementi(nodi_matrice[i].nodo,Nodo);
        if(confronto==0) break;
    }

    for(j=0;j<G->nsize;j++)
    {
        if(matrice[i][j]==1 || matrice[i][j]>0 || matrice[i][j]<0)
        {
            if(Ulti!=NULL)
            {
                //printf("\nCi stava gia' un valore, mi porto avanti con j per il prossimo 1 di indice:%d\n",j+1);

                while (j<G->nsize && Ulti!=NULL)
                {
                    confronto=G->confronto_elementi(nodi_matrice[j].nodo,Ulti);

                    if(confronto==0)
                    {
                        Ulti=NULL;
                        break;
                    }else
                    {
                        j++;
                    }
                }
            }
            else
            {
               // printf("\nho trovato un 1 all'indice:%d\n",j);
                salvaNodo=j;
                break;
            }
        }
    }

    if(salvaNodo!=-1)
        ultimo=nodi_matrice[salvaNodo].nodo;
    else ultimo=NULL;

    return ultimo;
}

int F_controllo_colore_bfs_lista(Grafo G, void *elem)
{
    // Posso avere archi quindi senza il puntatore al colore, devo andare a cercarlo
    L el=F_trova_elemento_bfs_lista(G,elem);

    if(((struct struttra_extra_colore*)el->extra)->colore==0) return 0;
    else return -1;
}

L F_trova_elemento_bfs_lista(Grafo  G, void *elem)
{
    L Lista = G->struttura;
    L adiacente = elem;

    while (Lista!=NULL)
    {
        int c=G->confronto_elementi(Lista->nodo,adiacente->nodo);
        if(c==0) {elem=Lista; break;}
        Lista=Lista->ptrNext;
    }

    return elem;
}


int F_controllo_colore_bfs_matrice(Grafo G, void *elem)
{
    void *c=F_trova_elemento_bfs_matrice(G,elem);
    C col=c;
    if(col->colore==0) return  0;
    else return -1;

    //Nm el=F_trova_elemento_bfs_matrice(G,elem);

    //if(((struct struttra_extra_colore*)el->extra)->colore==0) return 0;
    //else return -1;
}

/*Nm F_trova_elemento_bfs_matrice(Grafo G, void *elem)
{
    Nm adiacente=elem;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,confronto=0;

    for(i=0;i<G->nsize;i++)
    {
        confronto=G->confronto_elementi(adiacente,nodi_matrice[i].nodo);
        if(confronto==0) break;
    }

    adiacente=nodi_matrice[i].nodo;

    return adiacente;
}*/


void *F_trova_elemento_bfs_matrice(Grafo G, void *elem)
{
    Nm adiacente=elem;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,confronto=0;

    for(i=0;i<G->nsize;i++)
    {
        confronto=G->confronto_elementi(adiacente,nodi_matrice[i].nodo);
        if(confronto==0) break;
    }

    void* a=nodi_matrice[i].extra;

    return a;
}

void F_cambia_colore_bfs_lista(Grafo G,void *elem, int colore)
{
    L el=F_trova_elemento_bfs_lista(G,elem);

    ((struct struttra_extra_colore*)el->extra)->colore=colore;

}

void F_cambia_colore_bfs_matrice(Grafo G,void *elem, int colore)
{
    //Nm el=F_trova_elemento_bfs_matrice(G,elem);
    void *c=F_trova_elemento_bfs_matrice(G,elem);
    C col=c;
    col->colore=colore;
    // ((struct struttra_extra_colore*)el->extra)->colore=colore;
}

void F_stampa_bfs_lista(Grafo G,void *elem)
{
    L stampa = elem;
    G->stampa_elemento(stampa->nodo);
}

void F_stampa_bfs_matrice(Grafo G,void *elem)
{
    G->stampa_elemento(elem);

}

/* Generazione casuale di un valore float */
void *F_crea_float()
{
    float f=(float)rand()/(float)RAND_MAX;
    f=(rand()%100)+f;
    void *elemento=malloc(sizeof(float));
    memcpy(elemento,&f,sizeof(float));

    return elemento;
}

/* Funzione per la creazione di un elemento carattere */
void *F_crea_carattere()
{
    /* DICHIARAZIONE VARIABILI */
    int min=0,max=0;
    char c;

    void *elemento=malloc(sizeof(char));
    int scelta_carattere=rand()%2;

    switch(scelta_carattere)
    {
        case 0:
            min=65,max=90;
            break;

        case 1:
            min=97,max=122;
            break;
        default:
            puts("Error: creazione carattere non riuscita, inserimento carattere di dafault!");
            min=65,max=90;
            break;

    }
    c= (char) (rand() % (max - min) + min);
    memcpy(elemento,&c,sizeof(char));

    return elemento;
}

void *F_crea_stringa()
{
    /* DICHIARAZIONE VARIABILI*/
    int dim_stringa=0,scelta_carattere=0,i=0,max=0,min=0;
    char *stringa=NULL;

    /* Randomizzo la lunghezza della stringa */
    dim_stringa=4+(rand()%12);

    /* Alloco lo spazio necessario */
    stringa=malloc(sizeof(char)*dim_stringa);

    while(i<dim_stringa-1) // Ciclo eseguito dim_stringa -1 per inserire nell'ultimo elemento \0
    {
        scelta_carattere=rand()%3;

        switch(scelta_carattere)
        {
            /* Lettere A-Z maiuscole */
            case 0:
                min=65,max=90;
                break;

                /* Lettere A-Z minuscole */
            case 1:
                min=97,max=122;
                break;

                /* Numeri 0-9 */
            case 2:
                min=48,max=57;
                break;
            default:
                puts("Error: creazione stringa non riuscita, inserimento carattere di stringa di dafault!");
                min=65,max=90;
                break;
        }

        stringa[i]= (char) (rand() % (max - min ) + min);
        i++;
    }
    stringa[i]='\0';

    return stringa;
}


void *F_inserisci_carattere(int dim)
{
    /* DICHIARAZIONE VARIABILI*/
    char c='*';
    void *elemento=NULL;
    int flag=1;
    printf("\nTipologia di elemento di heap: CARATTERE. Inserire un solo carattere.\nEventuali altri caratteri verranno ignorati (Max: 1):");

    while(flag==1)
    {
        c= (char) getchar();
        if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        {
            flag=0;
        }
        else
        {
            while('\n'!=getchar());
            printf("Non e' stato inserito un carattere, riprovare:");
        }
    }

    while('\n'!=getchar());
    elemento=malloc(sizeof(char));
    memcpy(elemento,&c,sizeof(char));

    return elemento;
}

void *F_inserisci_stringa(int dim)
{
    /* DICHIARAZIONE VARIABILI */
    char *tmp=NULL,c='*';
    void *stringa_uscita=NULL;
    int i=0;

    tmp=(char *)malloc((dim+3)*sizeof(char)); // Default

    printf("\nInserisci la stringa (MAX:%d):",dim+2);

    for(i=0; (i<dim+2 && (c= (char) getchar()) != '\n' && c != EOF); i++)
    {
        tmp[i]=c;
    }
    tmp[i]='\0';

    stringa_uscita=malloc(i*sizeof(char)); // Allocazione del giusto spazio per stringhe minori di DIM_STRINGA
    strcpy(stringa_uscita,tmp); // Copia della stringa nello spazio abitio al suo contenimento
    free(tmp);

    return stringa_uscita;
}

void F_inizializza_pred(Grafo G)
{
    int i=0;
    Pred arrPred=(struct struttura_elemento_array_pred *)malloc(G->nsize* sizeof(struct struttura_elemento_array_pred));

    for(i=0;i<G->nsize;i++)
        arrPred[i].nodo=NULL;

    G->pred=arrPred;
}

void F_predecessoreBfs_lista(Grafo G, void *u,void *vAdiac)
{
    Pred arrayPred=G->pred;
    L Lista=G->struttura;
    int indice=-1,confronto=-1;
    L vAdiacente=vAdiac;

    while(Lista!=NULL)
    {
        indice++;
        confronto=G->confronto_elementi(Lista->nodo,vAdiacente->nodo);

       // printf("\n\nCONFRONTO |%d| CON |%d|\n\n",*((int *)Lista->nodo),*((int *)vAdiacente->nodo)); // CANC

        if(confronto==0) break;

        Lista=Lista->ptrNext;
    }

    arrayPred[indice].nodo=u;
   // L aa=u;
   // printf("\nHO MESSO QUALCOSA IN ARRAY all'indice [%d]\n -- Ho messo |%d|\n\n",indice,*((int *)aa->nodo));
}

void F_predecessoreBfs_matrice(Grafo G,void *u,void *vAdiac)
{
    Pred arrayPred=G->pred;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int indice=0,confronto=-1;

    for(indice=0;indice<G->nsize;indice++)
    {
        confronto=G->confronto_elementi(nodi_matrice[indice].nodo,vAdiac); // vAdiac potrebbe non contenere un cazzo (Si deve fare tipo vAdiac->nodo)
        if(confronto==0) break;
    }

    arrayPred[indice].nodo=u;
}

void *F_preleva_nodo_lista(Grafo G, int i)
{
    void *nodo=NULL;
    L Lista=G->struttura;
    int ind=0;

    for(ind=0;ind<i;ind++)
        Lista=Lista->ptrNext;

    if(Lista!=NULL) nodo=Lista;

    return nodo;
}

void *F_preleva_nodo_matrice(Grafo G, int i)
{
    void *nodo=NULL;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;

    if(nodi_matrice[i].nodo!=NULL) nodo=nodi_matrice[i].nodo;

    return nodo;
}

void *F_check_pred(Grafo G,int i)
{
    Pred arrayPred=G->pred;
    void *v=NULL;

    v=arrayPred[i].nodo;

    //if(arrayPred[i].nodo==NULL) puts("\nVUOTO\n\n"); // Canc
   // else {
      //  L vv=v;
      //  printf("\nNon vuoto: |%d|\n\n", *((int *) vv->nodo)); // Canc
   // }
    return v;
}

int F_trova_indice_elem_lista(Grafo G,void *elem)
{
    L Lista=G->struttura;
    int i=-1,confronto=-1;
    L el=elem;

    while(Lista!=NULL)
    {
        i++;
        confronto=G->confronto_elementi(Lista->nodo,el->nodo);
        if(confronto==0) break;
        Lista=Lista->ptrNext;
    }

    return i;
}

int F_trova_indice_elem_matrice(Grafo G,void *elem)
{
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,confronto=-1;

    for(i=0;i<G->nsize;i++)
    {
        confronto=G->confronto_elementi(nodi_matrice[i].nodo,elem);
        if(confronto==0) break;
    }

    return i;
}
