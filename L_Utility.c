//
// Created by ika on 8/13/2017.
//

#include <stdio.h>
#include "L_Grafo.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "L_Parser.h"
#include "L_Utility.h"
#include "L_Grafo.h"



/* Funzione principale */
void F_start()
{
    /* Generazione seme casuale */
    srand((unsigned)time(NULL));
    int menu_principale=-1,scelta=0;
    Grafo G = NULL;
    G=F_alloca_grafo(G);    // Funzione per l'allocazione della struttura principale per la gestione del grafo
    G=F_info_grafo(G);      // Funzione per l'inserimento delle proprieta' del grafo
    G=F_crea_grafo(G);      // Funzione per la creazione della struttura grafo
    G->stampa_generale(G);  // Stampa del grafo creato. Richiama: F_stampa_lista/matrice_adiacenza

    do
    {
        scelta=F_menu_principale(); // Stampa menu' principale
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

            case 7: // Visita in profondita'
                    F_visita_profondita(G);
                break;

            case 8: // Percorso tra due vertici
                    F_stampa_percorso(G);
                break;

            case 9:
                scelta=F_menu_avanzato(G->listmatr); // Stampa secondo menu'
                switch (scelta)
                {
                    case 1: // Aciclicità
                            F_grafo_ciclo(G);
                        break;
                    case 2: // Grafo casuale
                            F_grafo_casuale(G);
                        break;

                    case 3: // Converti grafo
                        F_converti_grafo(G);
                        break;

                    case 4: // Leggi scrivi grafo file
                        G=F_leggi_scrivi_grafo(G);
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

    /* Deallocazione struttura */
    if(G!=NULL)
        if(G->struttura!=NULL)
            G->dealloca_grafo(G->struttura,G);

}

/* Funzione di stampa del menu' principale */
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

/* Funzione di stampa del secondo menu' */
int F_menu_avanzato(int listmatr)
{
    int scelta = 0;
    puts("\n");
    puts("1] Verifica aciclicita' del grafo");
    puts("2] Genera un grafo casuale");
    if(listmatr==1) puts("3] Converti il grafo in una rappresentazione matriciale");
    else    puts("3] Converti il grafo in una rapparesentazione a lista");
    puts("4] Leggi/scrivi grafo su file");
    puts("");
    puts("0] Torna indietro");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'0','4',-1);

    return scelta;
}

/* Funzione di stampa per la gestione di un grafo da file */
int F_menu_leggi_scrivi_file()
{
    int scelta=0;

    puts("Operazione da svolgere:");
    puts("1] Scrivi il grafo corrente su file");
    puts("2] Leggi un grafo da file");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'1','2',0);

    return scelta;
}

/* Funzione per la lettura o scrittura di un grafo da file */
Grafo F_leggi_scrivi_grafo(Grafo G)
{
    int scelta=F_menu_leggi_scrivi_file(); // Menu' di scelta
    if(scelta==1 && G->struttura!=NULL)  F_salva_grafo(G);  // Salva le informazioni del grafo su file
    else G=F_leggi_grafo(G);    // Legge grafo da file

    return G;
}

/* Funzione per l'inserimento delle proprieta' del grafo */
Grafo F_info_grafo(Grafo G)
{
    int list_matr=0, tipo_dato=0, num_elem=0,peso=0;

    list_matr=F_list_matr();        // Scelta se lista adj o matrice
    tipo_dato=F_tipo_dato_grafo();  // Tipo di dato dei nodi
    peso=F_grafo_pesato();          // Scelta se pasato o meno
    num_elem=F_num_elem_grafo();    // Numero di elementi

    F_aggiungi_info(G,list_matr,tipo_dato,num_elem,peso); // Gestisce tutte le routine/callback

    return G;
}

/* Richiesta dell'aggiunta del peso al grafo */
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

/* Richiesta del tipo di grafo da usare */
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

/* Richiesta del tipo di dato contenuto nel grafo */
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

/* Richiesta del numero di elementi del grafo */
int F_num_elem_grafo()
{
    int scelta=0;

    printf("\nNumero di elementi da inserire:");
    scelta=F_seleziona(2,'0','9',0);

    return scelta;
}

/* Richiesta del tipo di grafo da generare */
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

/* Richiesta del tipo di visita da effetturare */
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

/* Funzione di inserimento di tutte le informazioni e callback per la gestione del grafo */
Grafo F_aggiungi_info(Grafo G,int list_matr,int tipo_dato,int num_elem,int peso)
{
    G->nsize=num_elem;      // Numero di nodi presenti
    G->infpeso=peso;        // 1=Grafo non pesato - 2=Grafo pesato
    G->listmatr=list_matr;  // 1=Lista Adj - 2=Matrice Adj
    G->tipodato=tipo_dato;  // 1=Int - 2=Float - 3=Char - 4=String
    G->pred=NULL;           // Array predecessori
    G->ciclo=0;             // 0=Ciclo presente - !0=No ciclo

    switch (list_matr)
    {
        case 1: // Lista Adj
            G->tipo_struttura=F_crea_lista_adj;                 // Funzione creazione della lista di Adj
            G->inserisci_arco=F_aggiungi_arco_lista;            // Funzione per l'aggiunta di un arco nella lista
            G->seleziona_nodo=F_seleziona_nodo_lista;           // Funzione per selezionare un elemento del grafo
            G->stampa_generale=F_stampa_lista_adiacenza;        // Funzione per la stampa generica del grafo
            G->check_nodo_uguale=F_check_nodo_uguale_lista;     // Funzione per la verifica dell'esistenza di un nodo
            G->inserisci_nodo=F_inserisci_nodo_lista;           // Funzione per l'inserimento di un nodo nella lista
            G->cancella_arco=F_cancella_arco_lista;             // Funzione per la cancellazione di un arco
            G->cancella_nodo=F_cancella_nodo_lista;             // Funzione per la cancellazione di un elemento nel grafo
            G->grafo_trasposto=F_trasposto_lista;               // Funzione per effetturare il trasposto del grafo lista
            G->dealloca_grafo=F_dealloca_grafo_lista;           // Funzione per deallocare il grafo
            G->converti_grafo=F_lista_a_matrice;                // Funzione per convertire il grafo in una matrice di Adj
            G->inizializza_bfsdfs=F_inizializza_bfsdfs_lista;   // Funzione di inizializzazione dell'array colore prima delle visite
            G->vertice_adiacente=F_vertice_adiacente_lista;     // Funzione per la ricerca del vertice adiacente
            G->check_color=F_controllo_colore_bfs_lista;        // Funzione per la verifica del colore di un nodo
            G->change_color=F_cambia_colore_bfs_lista;          // Funzione per cambiare colore di un nodo
            G->stampa_bfsdfs=F_stampa_bfs_lista;                // Funzione di stampa del grafo per la visita BFS
            G->predecessore_bfsdfs=F_predecessoreBfs_lista;     // Funzione di gestione dell'array pred
            G->preleva_nodo=F_preleva_nodo_lista;               // Funzione si selezione di un nodo di una lista
            G->indice_nodo=F_trova_indice_elem_lista;           // Funzione di selezione dell'indice di un nodo (usato per pred)
            G->verticedfs=F_verticeDfs_lista;                   // Funzione di visita in profondita' (richiama DFS_VISIT)
            break;
        case 2: // Matrice di Adj
            G->tipo_struttura=F_crea_matrice_adj;               // Funzione creazione della matrice di Adj
            G->inserisci_arco=F_aggiungi_arco_matrice;          // Funzione per l'aggiunta di un arco nella matrice
            G->seleziona_nodo=F_seleziona_nodo_matrice;         // Funzione per selezionare un elemento del grafo
            G->stampa_generale=F_stampa_matrice_adiacenza;      // Funzione per la stmapa generale della matrice di Adj
            G->check_nodo_uguale=F_check_nodo_uguale_matrice;   // Funzione per la verifica dell'esistenza di un nodo
            G->inserisci_nodo=F_inserisci_nodo_matrice;         // Funzione per l'inserimento di un nodo nella matrice
            G->cancella_arco=F_cancella_arco_matrice;           // Funzione per la cancellazione di un arco nella matrice
            G->cancella_nodo=F_cancella_nodo_matrice;           // Funzione per la cancellazione di un nodo nella matrice
            G->grafo_trasposto=F_trasposto_matrice;             // Funzione per effettuare il trasposto della matrice
            G->dealloca_grafo=F_dealloca_grafo_matrice;         // Funzione per deallocare il grafo
            G->converti_grafo=F_matrice_a_lista;                // Funzione per convertire la matrice in una lista di Adj
            G->inizializza_bfsdfs=F_inizializza_bfsdfs_matrice; // Funzione di inizializzazione dell'array colore prima delle visite
            G->vertice_adiacente=F_vertice_adiacente_matrice;   // Funzione per la ricerca dei vertici adiacenti
            G->check_color=F_controllo_colore_bfs_matrice;      // Funzione per il controllo del colore per la visita BFS
            G->change_color=F_cambia_colore_bfs_matrice;        // Funzione per il cambio del colore
            G->stampa_bfsdfs=F_stampa_bfs_matrice;              // Funzione per la stampa del grafo nella visita BFS
            G->predecessore_bfsdfs=F_predecessoreBfs_matrice;   // Funzione di gestione dell'array pred
            G->preleva_nodo=F_preleva_nodo_matrice;             // Funzione per prelevare un nodo dalla matrice
            G->indice_nodo=F_trova_indice_elem_matrice;         // FUnzione di selezione dell'indice di un nodo (usato per pred)
            G->verticedfs=F_verticeDfs_matrice;                 // Funzione di visita in profondita'
            break;
        default:
            puts("Error: selezione tipologia di struttura non valida!\n");
            exit(-1);
    }

    switch (tipo_dato)
    {
        /* Gestione degli elementi
         * F_crea_//; Creazione randomica del tipo di elemento
         * F_stampa_//: Stampa del tipo dell'elemento
         * F_confronto_//: Funzione per il confronto di elementi dello stesso tipo
         * F_dealloca_//: Deallocazione del singolo elemento
         * F_copia_dato_//: Copia del dato (memcpy)
         * F_salva_elem_//: Per la gestione del file, ne salva l'elemento
        * */
        case 1: // Intero
            G->tipo_elemento=F_crea_intero;
            G->stampa_elemento=F_stampa_intero;
            G->inserisci_elemento=F_inserisci_intero;
            G->confronto_elementi=F_confronto_interi;
            G->dealloca_elemento=F_dealloca_intero;
            G->copia_dato=F_copia_dato_intero;
            G->salvaelemgrafo=F_salva_elem_int;
            break;

        case 2: // Float
            G->tipo_elemento=F_crea_float;
            G->stampa_elemento=F_stampa_float;
            G->inserisci_elemento=F_inserisci_float;
            G->confronto_elementi=F_confronto_float;
            G->dealloca_elemento=F_dealloca_float;
            G->copia_dato=F_copia_dato_float;
            G->salvaelemgrafo=F_salva_elem_float;
            break;
        case 3: // Carattere
            G->tipo_elemento=F_crea_carattere;
            G->stampa_elemento=F_stampa_carattere;
            G->inserisci_elemento=F_inserisci_carattere;
            G->confronto_elementi=F_confronto_carattere;
            G->dealloca_elemento=F_dealloca_carattere_stringa;
            G->copia_dato=F_copia_dato_carattere;
            G->salvaelemgrafo=F_salva_elem_char;
            break;
        case 4: // Stringa
            G->tipo_elemento=F_crea_stringa;
            G->stampa_elemento=F_stampa_stringa;
            G->inserisci_elemento=F_inserisci_stringa;
            G->confronto_elementi=F_confronto_stringa;
            G->dealloca_elemento=F_dealloca_carattere_stringa;
            G->copia_dato=F_copia_dato_stringa;
            G->salvaelemgrafo=F_salva_elem_string;
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

    do
    {
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            if(c>=minimo && c<=massimo)
            {
                tmp[i]=c;
                i++;
            }

        }
        intero_preso = (int) strtol(tmp, &ptr, 10);

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

/* Funzione per la creazione della struttura principale di tipo lista di Adj */
Grafo F_crea_matrice_adj(Grafo G)
{
    // Allocazione della struttura della matrice e dell'array che contiene i nodi del grafo
    M struttura_matrice = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)malloc(G->nsize* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL; // Generica: usata per collegare l'informazione sul colore del singolo nodo

    int i=0;
    for(i=0;i<G->nsize;i++)
    {
        // Creazione randomica dell'elemento e inserimento nell'array
        void *elem=G->tipo_elemento();
        array_nodo_matrice[i].nodo=elem;
    }
    struttura_matrice->nodo=array_nodo_matrice; // Inserimento dell'array

    float **matrice =(float **)malloc(G->nsize* sizeof(float *)); // Creazione della matrice
    for(i=0;i<G->nsize;i++)
        matrice[i]=(float *)malloc(G->nsize* sizeof(float *));

    // Salvataggio delle informazioni e inizializzazione della matrice
    struttura_matrice->matrice=matrice;
    G->struttura=struttura_matrice;
    F_inizializza_matrice(G);

    return G;
}

/* Funzione di inizializzazione della matrice */
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

/* Funzione di stampa generica della matrice di Adj */
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
        G->stampa_elemento(nodi_matrice[i].nodo); // Richiama: 
    }

    puts("\n\nMatrice di riferimento:");
    for(i=0;i<G->nsize;i++) {
            printf("[%d]:\t",i);

        for (j = 0; j < G->nsize; j++) {
            if(matrice[i][j]>0 || matrice[i][j]<0)
               printf("|1|\t");
            else printf("|0|\t");
        }
        puts("");
    }
    puts("\n");
}

/* Stampa il peso di un grafo in una matrice di Adj */
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

/* Creazione della lista di Adj */
Grafo F_crea_lista_adj(Grafo G)
{
   L listaAdj = NULL;
   int i=0;
   for(i=0;i<G->nsize;i++)
     {
       void *elem=G->tipo_elemento(); // Richiama: F_crea_intero/float/carattere/stringa
       listaAdj=F_alloca_elemento_lista(listaAdj, elem);
     }
     G->struttura=listaAdj; // Inserimento della lista nella struttura principale

    return G;
}

/* Creazione di un elemento della lista di Adj */
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

/* Funzione di stampa generica della lista di Adj */
void F_stampa_lista_adiacenza(Grafo G)
{
    L Lista=G->struttura;
    int i=0;
    if(G->infpeso==1) puts("\nStruttura della lista: \n[Indice]:[Nodo]->[Nodo]\n");
    else // Verifica se il grafo e' pesato
    {
        puts("\nStruttura della lista: \n[Indice]:[Nodo]-(Peso)->[Nodo]\n");
        F_stampa_peso_lista_adiacenza(G);
    }
    while (Lista!=NULL)
    {
        printf("[%d]:",i);
        G->stampa_elemento(Lista->nodo); // Richiama: F_stampa_intero/float/carattere/stringa
        L Arco = Lista;

        if(Arco->ptrArco == NULL) puts("");
        else // Stampa degli archi
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

/* Stampa il peso di un grafo in lista di Adj */
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
            G->stampa_elemento(Lista->ptrArco->nodo); // Richiama: F_stampa_intero/float/carattere/stringa

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

/* Genera un valore intero random */
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

/* Aggiunta di un arco in una lista di Adj */
void F_aggiungi_arco_lista(Grafo G,int p,int a)
{
    L lista = G->struttura;
    L elem_lista_a = NULL;
    int i = 0,checkArco=0;
    void *elem=F_preleva_elem_lista(lista,a);   // Seleziona l'elemento di arrivo scelto dall'utente
    elem_lista_a=F_alloca_elemento_lista(elem_lista_a,elem); // Viene creato un nuovo elemento con il punttore allo stesso dato di quello scelto

    for(i=0;i<p;i++) // Si porta al nodo di partenza
        lista=lista->ptrNext;

    /* Verifica se e' gia' presente un arco tra i nodi scelti */
    if(lista->ptrArco!=NULL)
    {
       L checkArcoPresente = lista;
       while (checkArcoPresente != NULL)
       {
           if (elem_lista_a->nodo == checkArcoPresente->nodo)
           {
               if(G->infpeso!=1) // Viene chiesto all'utente se desidera cambiare il peso
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
    /* Si procede all'inserimento dell'arco solo se non presente */
    if(!checkArco) {
        lista->ptrArco = elem_lista_a;

        if (G->infpeso != 1) // Pesato
        {
            void *pe=F_inserisci_float(6);
            float peso = *((float *)pe);
            P stpeso = F_alloca_struttura_peso(peso);
            elem_lista_a->ptrPeso = stpeso;
        }
    }
}

/* Permette all'utente di cambiare il peso di un nodo gia' presente */
int F_cambia_peso_lista(L elem,StampaElemento stampa_elemento)
{
    printf("\nE' gia' presente un arco pesato che arriva al nodo:");
    stampa_elemento(elem->nodo);
    int scelta = F_menu_scelta_cambio_peso();

    if(scelta==1) { // Si cambia il peso
        void *p=F_inserisci_float(6);
        float peso=*((float *)p);
        elem->ptrPeso->peso=peso;
    }
    else
        puts("");  // Usato per evitare deep indentation

    return 1;
}

/* Menu' di scelta per il cambio del peso di un arco */
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

/* Alloca la struttura per gestire il peso di un arco */
P F_alloca_struttura_peso(float peso)
{
    P new_elem = (struct struttura_grafo_pesato *)malloc(sizeof(struct struttura_grafo_pesato));
    new_elem->peso=peso;

    return new_elem;
}

/* Seleziona un nodo della lista di Adj in base all'indice passato */
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

/* Aggiunge un arco tra due nodi di una matrice di Adj */
void F_aggiungi_arco_matrice(Grafo G,int p,int a)
{
    M matrice = G->struttura;
    Nm nodi_matrice = matrice->nodo;
    int scelta = 0;

    if(G->infpeso!=1) // Pesato
    {
        if(matrice->matrice[p][a]>0 || matrice->matrice[p][a]<0) // Arco gia' presente
        {
            printf("\nE' gia' presente un arco pesato che arriva al nodo: ");
            G->stampa_elemento(nodi_matrice[a].nodo);
            scelta = F_menu_scelta_cambio_peso();
        }

        if(scelta==1 || matrice->matrice[p][a]==0) {
            void *pe=F_inserisci_float(6);
            float peso=*((float *)pe);
            matrice->matrice[p][a] = peso;
        }
    }
    else
    matrice->matrice[p][a]=1; // Inserimento in grafo non pesato
}

/* Richiesta all'utente di selezionare un nodo della lista di Adj */
int F_seleziona_nodo_lista(Grafo G)
{
    printf("\nInserisci l'indice dell'elemento che vuoi selezionare:");
    int indice = F_seleziona_indice(5,G->nsize);

    return indice;
}

/* Richiesta all'utente di selezionare un nodo della matrice di Adj */
int F_seleziona_nodo_matrice(Grafo G)
{
    printf("\nInserisci l'indice dell'elemento che vuoi selezionare:");
    int indice = F_seleziona_indice(5,G->nsize);

    return indice;
}

/* Funzione che richiede all'utente di inserire l'indice del nodo su cui effettuare le operazioni */
int F_seleziona_indice(int dim, int nsize)
{
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;

    for(i=0;i<dim;i++)
        tmp[i]='*';
    i=0;

    do
    {
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            if(c>='0' && c<='9')
            {
                tmp[i]=c;
                i++;
            }

        }

        intero_preso = (int) strtol(tmp, &ptr, 10);
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
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0;


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
    intero_preso = (int) strtol(tmp, &ptr, 10);
    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));

    return elemento;
}

/* Funzione per l'inserimento da parte dell'utente di un dato float */
void *F_inserisci_float(int dim)
{
    char tmp[dim],c='*';
    int i=0;
    float ftemp;

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

    ftemp=strtof(tmp,NULL);
    void *elemento=malloc(sizeof(float));

    printf("\nSi vuole esprimere il valore: [%f] in negativo?\n1-Si\n2-No\nSeleziona tramite valore numerico:",ftemp);
    int scelta = F_seleziona(1,'1','2',0);
    if(scelta==1) ftemp=F_ritorna_negativo(ftemp);
    memcpy(elemento,&ftemp,sizeof(float));

    return elemento;
}

/* Ritorno il valore float in negativo */
float F_ritorna_negativo(float num)
{
    num=(num)*(-1);
    return num;
}

/* Verifica se e' gia' presente un nodo con il medesimo dato nella lista di Adj */
int F_check_nodo_uguale_lista(Grafo G,void *elem)
{
    int controllo = 0,i=0;
    L lista = G->struttura;

    while (lista!=NULL)
    {
        i = G->confronto_elementi(lista->nodo,elem); // Richiama: F_confronto_interi/float/carattere/stringa
        if(i==0)
        {
            controllo=1;
            break;
        }

        lista=lista->ptrNext;
    }

    return controllo; // Return 0=Nodo uguale non presente. 1=Presente
}

/* Verifica se e' gia' presente un nodo con il medesimo dato nella matrice di Adj */
int F_check_nodo_uguale_matrice(Grafo G,void *elem)
{
    int i=0,controllo=0,j=0;
    M Matrice = G->struttura;
    Nm nodo_matrice = Matrice->nodo;

    for(i=0;i<G->nsize;i++)
        {
            j = G->confronto_elementi(nodo_matrice[i].nodo,elem);  // Richiama: F_confronto_interi/float/carattere/stringa
            if(j==0)
            {
                controllo=1;
                break;
            }
        }

    return controllo; // Return 0=Nodo uguale non presente. 1=Presente
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

/* Inserimento di un nuovo nodo in una lista di Adj */
void F_inserisci_nodo_lista(Grafo G,void *elem)
{
    L Lista = G->struttura;
    L NewLista = F_alloca_elemento_lista(Lista,elem);
    G->nsize=G->nsize+1; // Mantiene l'informazione del mumero dei nodi presenti
    G->struttura=NewLista;
}

/* Inserimento di un nuovo nodo in una matrice di Adj */
void F_inserisci_nodo_matrice(Grafo G,void *elem)
{
    int i=0,new_size=(G->nsize+1);
    M struttura_matrice = G->struttura;
    float **matrice_old=struttura_matrice->matrice;

    /* Creazione della nuova matrice di Adj */
    float **matrice_new=(float **)malloc(new_size* sizeof(float *));
    for(i=0;i<new_size;i++)
          matrice_new[i]=(float *)malloc(new_size* sizeof(float *));

    /* Copia delle informazioni della vecchia matrice */
    F_copia_matrice(matrice_new,matrice_old,G->nsize);
    Nm nodi_matrice = struttura_matrice->nodo;
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)realloc(nodi_matrice,new_size* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL;
    array_nodo_matrice[G->nsize].nodo=elem;

    /* Deallocazione matrice */
    for(i=0;i<G->nsize;i++)
        free(matrice_old[i]);
    free(matrice_old);

    /* Inserimento della nuova matrice nella struttura principale */
    G->nsize=new_size;
    struttura_matrice->nodo=array_nodo_matrice;
    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
}

/* Inizializza la nuova matrice e ne copia le informazioni degli archi dalla vecchia */
void F_copia_matrice (float ** destmat, float ** srcmat,int dim)
{
    int i=0,j=0;

    for(i=0;i<dim+1;i++)
        for(j=0;j<dim+1;j++)
            destmat[i][j]=0;

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            destmat[i][j] = srcmat[i][j];
}

/* Inizializza la nuova matrice e ne copia le informazioni degli archi dalla vecchia (usata per il trasposto) */
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

/* Eliminazione di un arco nella lista di Adj */
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
            c = G->confronto_elementi(Nodo_p->ptrArco->nodo, Elem_a); // Richiama: F_confronto_interi/float/carattere/stringa

            if (c == 0) // Trovato
            {
                L Tmp = Nodo_p->ptrArco;
                if (Nodo_p->ptrArco->ptrArco != NULL) // C'è qualcosa dopo
                {
                    Nodo_p->ptrArco=Nodo_p->ptrArco->ptrArco;
                } else {
                    Nodo_p->ptrArco = NULL;
                }
                free(Tmp); // Non si deve deallocare l'elemento in quando sono puntatori alla struttura principale
                break;
            }
        }
        Nodo_p=Nodo_p->ptrArco;
    }

    if(c!=0) printf("\nNodo non presente!\n");
    else printf("\nDeallocazione effettuata!\n");
}

/* Eliminazione di un arco nella matrice di Adj */
void F_cancella_arco_matrice(Grafo G,int p,int a)
{
    M matrice = G->struttura;
    matrice->matrice[p][a]=0;
}

/* Deallocazione di un valore di tipo intero */
void F_dealloca_intero(void *elem)
{
    free(((int *)elem));
}

/* Deallocazione di un valore di tipo carattere o stringa */
void F_dealloca_carattere_stringa(void *elem)
{
    free(((char *)elem));
}

/* Deallocazione di un valore di tipo float */
void F_dealloca_float(void *elem)
{
    free(((float *)elem));
}

/* Cancella un nodo della matrice di Adj */
void F_cancella_nodo_matrice(Grafo G,int c)
{
    int new_size=(G->nsize-1),i=0,j=0,ni=0,nj=0;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    float **matrice_old=struttura_matrice->matrice;

    /* Creazione della nuova matrice */
    float **matrice_new=(float **)malloc(new_size* sizeof(float *));
    for(i=0;i<new_size;i++)
        matrice_new[i]=(float *)malloc(new_size* sizeof(float *));

    /* Copia dei valori della vecchia lista escludendo il nodo scelto */
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
    /* Copia dell'array contenente i nodi della lista */
    for(i=c;i<new_size;i++)
        nodi_matrice[i]=nodi_matrice[i+1];
    free(matrice_old);

    /* Inserimento delle informazioni nella nuova matrice */
    nodi_matrice = (struct struttura_elemento_array_nodo_matrice *)realloc(nodi_matrice,new_size* sizeof(struct struttura_elemento_array_nodo_matrice));
    nodi_matrice->extra=NULL;
    struttura_matrice->nodo=nodi_matrice;
    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
    G->nsize=new_size;
}

/* Cancella un nodo della lista di Adj */
void F_cancella_nodo_lista(Grafo G,int c)
{
    L Lista = G->struttura,curr=NULL,prec=NULL,Lista_del=Lista;

    if(Lista!=NULL) {
        int i=0,confronto;
        /* Preleva il nodo da eliminare */
        for(i=0;i<c;i++)
            Lista_del=Lista_del->ptrNext;

        void *elem_del = Lista_del->nodo;

        L Tmp=Lista;

        /* Cancellazione del nodo e degli eventuali arhci presenti */
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


        if(i==0) // Testa
        {
            Tmp=Lista;
            Lista=Lista->ptrNext;
        }
        else
        {
            int s=0;
            L CodaMezz=Lista;
            if(i==(G->nsize-1)) // Coda
            {
                for(;s<(G->nsize-2);s++)
                    CodaMezz=CodaMezz->ptrNext;

                Tmp=CodaMezz->ptrNext;
                CodaMezz->ptrNext=NULL;
            } else // In mezzo
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

/* Effettua il trasposto della lista di Adj */
void F_trasposto_lista(Grafo G)
{
    L Lista_old = G->struttura;
    L Lista_new = NULL;
    L ListaOldPrinc = G->struttura;
    int controllo = 0;
    float InfPeso = 0;

    while (ListaOldPrinc!=NULL)
    {
        /* Allocazione in coda dei nodi del grafo */
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

    ListaOldPrinc=G->struttura; // Lista vecchia
    L ListaNewPrinc=Lista_new;  // Lista nova

    while(ListaOldPrinc!=NULL)
    {
        L ArcoOld = ListaOldPrinc->ptrArco;

        /* Verifica esistenza arco */
        while (ArcoOld!=NULL)
        {
            if(G->infpeso!=1) InfPeso=ArcoOld->ptrPeso->peso; // Salva il valore del peso

            /* Ricerca del nodo nella nuova lista */
            while(ListaNewPrinc!=NULL)
            {
                controllo=G->confronto_elementi(ArcoOld->nodo,ListaNewPrinc->nodo); // Trova il nodo nella nuova lista
                if(controllo==0) break;
                ListaNewPrinc=ListaNewPrinc->ptrNext;
            }
            L ListaNewPartenza=NULL;
            if(ListaNewPrinc!=NULL)
            {
               ListaNewPartenza=ListaNewPrinc;
               ListaNewPrinc=Lista_new;
            }
            else{puts("\nERROR: arco grafo trasposto"); exit(-4);}

            void *ArrivoOld = ListaOldPrinc->nodo;

            /* Ricerca del nodo collegato all'arco nella nuova lista */
            while(ListaNewPrinc!=NULL)
            {
                controllo=G->confronto_elementi(ArrivoOld,ListaNewPrinc->nodo);
                if(controllo==0) break;
                ListaNewPrinc=ListaNewPrinc->ptrNext;
            }
            /* Inserimento dell'arco */
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
    /* Deallocazione vecchia lista */
    F_dealloca_grafo_lista(Lista_old,G);
    G->struttura=Lista_new;
}

/* Deallocazione del grafo in lista di Adj */
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
            if(G->infpeso!=1) // eliminazione della struttura contenente il peso
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

    while (ListaPrinc!=NULL) // eliminazione del valori dei nodi
    {
        TmpNext=ListaPrinc->ptrNext;
        G->dealloca_elemento(ListaPrinc->nodo);
        ListaPrinc=TmpNext;
    }

    puts("\nHo deallocato la lista precedente!\n");
}

/* Deallocazione del grafo in matrice di Adj */
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

/* Effettua il trasposto della matrice di Adj */
void F_trasposto_matrice(Grafo G)
{
    int i=0,j=0;
    M struttura_matrice = G->struttura;
    float **matrice_old=struttura_matrice->matrice;

    /* Creazione della nuova matrice */
    float **matrice_new=(float **)malloc(G->nsize* sizeof(float *));
    for(i=0;i<G->nsize;i++)
        matrice_new[i]=(float *)malloc(G->nsize* sizeof(float *));
    /* Copio i valori della matrice principale in quella copiata (usata per comodo) */
    F_copia_matrice_identica(matrice_new,matrice_old,G->nsize);
    /* Inizializzo la matrice principale */
    F_inizializza_matrice(G);

    /* Copio i valori invertengo riga/colonna */
    for(i=0;i<G->nsize;i++)
        for(j=0;j<G->nsize;j++)
        {
            if(matrice_new[i][j] < 0 || matrice_new[i][j] > 0)
                matrice_old[j][i]=matrice_new[i][j];
        }
    /* Dealloco la matrice creata */
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

/* Trasforma la matrice in lista di Adj */
void F_matrice_a_lista(Grafo G)
{
    int i=0,j=0,k=0;
    L Lista_new=NULL;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;

    for(i=0;i<G->nsize;i++)
    {
        /* Copia in coda dei nodi presenti */
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
            if(matrice[i][j]>0 || matrice[i][j]<0) // E' presente un arco
            {
                /* Prelevo i nodi di riferimento di riga e colonna */
                for(k=0;k<i;k++)
                    ListaRiga=ListaRiga->ptrNext;

                for(k=0;k<j;k++)
                    ListaColonna=ListaColonna->ptrNext;

                if(ListaRiga==NULL || ListaColonna==NULL) {puts("\nError: conversione matrice a lista!"); exit(-10);}
                L newElLista = NULL;
                newElLista=F_alloca_elemento_lista(newElLista,ListaColonna->nodo);

                if(G->infpeso!=1) // Pesato
                {
                   P newPeso=F_alloca_struttura_peso(matrice[i][j]);
                   newElLista->ptrPeso=newPeso;
                }

                if(ListaRiga->ptrArco!=NULL) // Inserisco l'arco con le relative informazioni
                {
                    newElLista->ptrArco=ListaRiga->ptrArco;
                    ListaRiga->ptrArco=newElLista;
                }else ListaRiga->ptrArco=newElLista;
                ListaRiga=Lista_new; ListaColonna=Lista_new;
            }
        }

    G=F_aggiungi_info(G,1,G->tipodato,G->nsize,G->infpeso); // Correggo le callback e le info per una lista
    G->struttura=Lista_new;
}

/* Trasforma la lista in matrice di Adj */
void F_lista_a_matrice(Grafo G)
{
    int i=0,j=0,controllo=-1;
    L Lista=G->struttura;
    L ListaScorr=Lista;

    M struttura_matrice = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    Nm array_nodo_matrice = (struct struttura_elemento_array_nodo_matrice *)malloc(G->nsize* sizeof(struct struttura_elemento_array_nodo_matrice));
    array_nodo_matrice->extra=NULL;
    /* Alloca la nuova matrice */
    float **matrice_new=(float **)malloc(G->nsize* sizeof(float *));
    for(i=0;i<G->nsize;i++)
        matrice_new[i]=(float *)malloc(G->nsize* sizeof(float *));

    struttura_matrice->matrice=matrice_new;
    G->struttura=struttura_matrice;
    F_inizializza_matrice(G);

    /* Copia dei nodi della lista nell'array in riferimento alla matrice */
    for(i=0;i<G->nsize;i++)
    {
        void *newEl=G->copia_dato(ListaScorr->nodo);
        array_nodo_matrice[i].nodo=newEl;
        ListaScorr=ListaScorr->ptrNext;
    }
    struttura_matrice->nodo=array_nodo_matrice;
    ListaScorr=Lista;
    /* Ricerca di archi e copia delle informazioni nella matrice */
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
    F_dealloca_grafo_lista(Lista,G); // Eliminazione della lista
    G=F_aggiungi_info(G,2,G->tipodato,G->nsize,G->infpeso); // Correggo le callback e le info per una matrice
}

/* Funzione di inizializzazione dell'array per lista colore prima delle visite */
void *F_inizializza_bfsdfs_lista(Grafo G,int s,int df)
{
    L Nodo_s=NULL;
    int cont=0;
    L Lista=G->struttura;

    while(Lista!=NULL)
    {
        /* Alloca la struttura per mantenere l'informazione del colore del nodo */
        C newColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));

        if(cont==s) { // (Solo BFS) al nodo selezionato viene inserito il colore grigio=1
            if(df==0) newColore->colore=1; // Verifica se bfs o dfs
            else newColore->colore=0;   // In dfs restano tutti i nodi bianchi=0

            Nodo_s=Lista;
        }
        else newColore->colore=0;
        /* Collego la struttura colore */
        Lista->extra=newColore;
        Lista=Lista->ptrNext;
        cont++;
    }
    // Ritorno il nodo per verifica e per stamparlo
    return Nodo_s;
}

/* Funzione di inizializzazione dell'array colore per matrice prima delle visite */
void *F_inizializza_bfsdfs_matrice(Grafo G,int s,int df)
{
    /* Commenti di riferimento in: F_inizializza_bfsdfs_lista */
    Nm Nodo_s=NULL;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,j=0;

    for(i=0;i<G->nsize;i++)
    {
        C newColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));

        if(i==s)
        {
            if(df==0) newColore->colore=1;
            else newColore->colore=0;

            Nodo_s=nodi_matrice[i].nodo;
        } else newColore->colore=0;

        nodi_matrice[i].extra=newColore;
    }

    return Nodo_s;
}

/* Ritorna il vertice adiacente, se presente, in una lista di Adj */
void *F_vertice_adiacente_lista(Grafo G,void *u, void *ultimo)
{
    int controllo=-1;
    L Nodo=u;
    L Ulti=ultimo;
    L Lista=G->struttura;
    /*
     * Ultimo rappresenta l'ultimo nodo che e' stato passato come vertice adiacente.
     * La prima volta ultimo risulta=NULL e la funzione restituisce il primo vertice,
     * i successivi ultimo saranno uguali all'utlimo vertice ritornato dalla funzione.
     * In questo modo viene cercato il successivo vertice adiacente partendo dall'informazione
     * in ultimo.
     * */

    while (Lista!=NULL)
    {
        controllo=G->confronto_elementi(Lista->nodo,Nodo->nodo);
        if(controllo==0) break;
        Lista=Lista->ptrNext;
    }
    Nodo=Lista;

    if(Nodo->ptrArco!=NULL) {

        if (ultimo != NULL) { // E' stato gia' preso un adiacente

            while (Nodo!=NULL) {

                controllo = G->confronto_elementi(Nodo->nodo, Ulti->nodo);
                if(controllo==0) {
                    if(Nodo->ptrArco!=NULL) ultimo=Nodo->ptrArco;
                    else ultimo=NULL;
                    break;
                }

                Nodo=Nodo->ptrArco;
            }

        } else ultimo=Nodo->ptrArco; // Primo vertice adiacente trovato
    }

    return ultimo;
}

/* Ritorna il vertice adiacente, se presente, in una matrice di Adj */
void *F_vertice_adiacente_matrice(Grafo G,void *u, void *ultimo)
{
    Nm Nodo=u;
    Nm Ulti=ultimo;
    M struttura_matrice = G->struttura;
    float **matrice=struttura_matrice->matrice;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0, j=0,salvaNodo=-1,confronto=-1;

    /*
     * Ultimo rappresenta l'ultimo nodo che e' stato passato come vertice adiacente.
     * La prima volta ultimo risulta=NULL e la funzione restituisce il primo vertice,
     * i successivi ultimo saranno uguali all'utlimo vertice ritornato dalla funzione.
     * In questo modo viene cercato il successivo vertice adiacente partendo dall'informazione
     * in ultimo.
     * */

    for(i=0;i<G->nsize;i++) // Seleziono la riga i
    {
        confronto=G->confronto_elementi(nodi_matrice[i].nodo,Nodo);
        if(confronto==0) break;
    }

    for(j=0;j<G->nsize;j++)
    {
        if(matrice[i][j]==1 || matrice[i][j]>0 || matrice[i][j]<0) // Trovato vertice
        {
            if(Ulti!=NULL) // E' stato gia' preso un vertice adiacente
            {
                while (j<G->nsize && Ulti!=NULL) // Ricerca del successivo vertice se presente
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
            else // Primo vertice adiacente trovato
            {
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

/* Funzione per la verifica del colore di un nodo nella lista di Adj */
int F_controllo_colore_bfs_lista(Grafo G, void *elem)
{
    // Elem=posso avere archi quindi senza il puntatore al colore, devo andare a cercarlo
    L el=F_trova_elemento_bfs_lista(G,elem);

    /* Accesso alla struttura contenente il colore */
    if(((struct struttra_extra_colore*)el->extra)->colore==0) return 0;
    return ((struct struttra_extra_colore*)el->extra)->colore;
}

/* Ritorna il nodo della struttura principale in lista di Adj */
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

/* Funzione per la verifica del colore di un nodo nella matrice di Adj */
int F_controllo_colore_bfs_matrice(Grafo G, void *elem)
{
    void *c=F_trova_elemento_bfs_matrice(G,elem);
    C col=c;
    if(col->colore==0) return  0;
    else return col->colore;
}

/* Ritorna il nodo della struttura principale in matrice di Adj */
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

/* Cambia il colore del nodo con il valore passato per lista Adj */
void F_cambia_colore_bfs_lista(Grafo G,void *elem, int colore)
{
    L el=F_trova_elemento_bfs_lista(G,elem);
    ((struct struttra_extra_colore*)el->extra)->colore=colore;
}

/* Cambia il colore del nodo con il valore passato per matrice Adj */
void F_cambia_colore_bfs_matrice(Grafo G,void *elem, int colore)
{
    void *c=F_trova_elemento_bfs_matrice(G,elem);
    C col=c;
    col->colore=colore;
}

/* Stampa generica per BFS */
void F_stampa_bfs_lista(Grafo G,void *elem)
{
    L stampa = elem;
    G->stampa_elemento(stampa->nodo); // Richiama: F_stampa_intero/float/carattere/stringa
}

/* Stampa BFS per matrice */
void F_stampa_bfs_matrice(Grafo G,void *elem)
{
    G->stampa_elemento(elem); // Richiama: F_stampa_intero/float/carattere/stringa
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

/* Funzione per la creazione di un elemento stringa */
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

/* Prende in input un elemento carattere */
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

/* Prende in input un elemento di tipo stringa */
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

/* Inizializza l'array dei predecerssori */
void F_inizializza_pred(Grafo G)
{
    int i=0;
    Pred arrPred=(struct struttura_elemento_array_pred *)malloc(G->nsize* sizeof(struct struttura_elemento_array_pred));

    for(i=0;i<G->nsize;i++)
        arrPred[i].nodo=NULL;

    G->pred=arrPred; // Inserimento nella struttura generale
}

/* Gestione del'array dei predecessori per lista Adj */
void F_predecessoreBfs_lista(Grafo G, void *u,void *vAdiac)
{
    Pred arrayPred=G->pred;
    L Lista=G->struttura;
    int indice=-1,confronto=-1;
    L vAdiacente=vAdiac;

    /* trovo l'indice dell'elemento */
    while(Lista!=NULL)
    {
        indice++;
        confronto=G->confronto_elementi(Lista->nodo,vAdiacente->nodo); // Richiama: F_confronto_interi/float/carattere/stringa

        if(confronto==0) break;

        Lista=Lista->ptrNext;
    }

    arrayPred[indice].nodo=u;
}

/* Gestione del'array dei predecessori per matrice Adj */
void F_predecessoreBfs_matrice(Grafo G,void *u,void *vAdiac)
{
    Pred arrayPred=G->pred;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int indice=0,confronto=-1;

    for(indice=0;indice<G->nsize;indice++)
    {
        confronto=G->confronto_elementi(nodi_matrice[indice].nodo,vAdiac); // Richiama: F_confronto_interi/float/carattere/stringa
        if(confronto==0) break;
    }
    arrayPred[indice].nodo=u;
}

/* Ritorna un nodo della lista in base all'indice passato */
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

/* Ritorna un nodo della matrice in base all'indice passato */
void *F_preleva_nodo_matrice(Grafo G, int i)
{
    void *nodo=NULL;
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;

    if(nodi_matrice[i].nodo!=NULL) nodo=nodi_matrice[i].nodo;

    return nodo;
}

/* Ritorna il nodo presente nell'array */
void *F_check_pred(Grafo G,int i)
{
    Pred arrayPred=G->pred;
    void *v=NULL;
    v=arrayPred[i].nodo;

    return v;
}

/* Ritorna l'indice dell'elemento passato in una lista di Adj */
int F_trova_indice_elem_lista(Grafo G,void *elem)
{
    L Lista=G->struttura;
    int i=-1,confronto=-1;
    L el=elem;

    while(Lista!=NULL)
    {
        i++;
        confronto=G->confronto_elementi(Lista->nodo,el->nodo); // Richiama: F_confronto_interi/float/carattere/stringa
        if(confronto==0) break;
        Lista=Lista->ptrNext;
    }

    return i;
}

/* Ritorna l'indice dell'elemento passato in una matrice di Adj */
int F_trova_indice_elem_matrice(Grafo G,void *elem)
{
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0,confronto=-1;

    for(i=0;i<G->nsize;i++)
    {
        confronto=G->confronto_elementi(nodi_matrice[i].nodo,elem); // Richiama: F_confronto_interi/float/carattere/stringa
        if(confronto==0) break;
    }

    return i;
}

/* DFS: lista */
void F_verticeDfs_lista(Grafo G)
{
    L Lista=G->struttura; G->ciclo=0;

    while (Lista!=NULL)
    {
        if(((struct struttra_extra_colore*)Lista->extra)->colore==0)
            F_Dfs_visit(G,Lista);

        Lista=Lista->ptrNext;
    }
}

/* DFS: matrice */
void F_verticeDfs_matrice(Grafo G)
{
    M struttura_matrice = G->struttura;
    Nm nodi_matrice = struttura_matrice->nodo;
    int i=0;  G->ciclo=0;

    for(i=0;i<G->nsize;i++)
    {
        C col=nodi_matrice[i].extra;
        if(col->colore==0) F_Dfs_visit(G,nodi_matrice[i].nodo);
    }
}
