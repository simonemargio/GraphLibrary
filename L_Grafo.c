#include <stdio.h>
#include <stdlib.h>
#include "L_Utility.h"
#include "L_Coda.h"

/* Funzione per l'allocazione della struttura principale per la gestione del grafo */
Grafo F_alloca_grafo(Grafo G)
{
    G = (struct struttura_gestione_grafo *) malloc (sizeof(struct struttura_gestione_grafo));
    G->struttura=NULL;
    return G;
}


/* Funzione per la creazione della struttura grafo */
Grafo F_crea_grafo(Grafo G)
{
    if(G!=NULL) G=G->tipo_struttura(G); // Richiama: F_crea_lista/matrice_adj
    else
    {
        puts("\nError: stuttura non presente!\n");
        exit (-1);
    }
    return  G;
}

/* Aggiunta di un arco al grafo */
void F_aggiungi_arco(Grafo G)
{
    if(G!=NULL)
    {
        G->stampa_generale(G); // Richiama: F_stampa_lista/matrice_adiacenza (stampa generica)
        /* Seleziono i nodi per l'inserimento dell'arco e ne verifico l'esistenza */
        printf("\nSeleziona il nodo di partenza");
        int p=G->seleziona_nodo(G); // Richiama: F_seleziona_nodo_lista/matrice
        printf("\nSeleziona il nodo d'arrivo");
        int a=G->seleziona_nodo(G);
        if(p >= G->nsize || a >= G->nsize || p==a) puts("\nIndici selezionati non validi!");
        else G->inserisci_arco(G,p,a); // Richiama: F_aggiungi_arco_lista/matrice
    }
    else
        puts("Struttura non presente!\n");
}

/* Aggiunge un nuovo vertice al grafo */
void F_aggiungi_vertice(Grafo G)
{
    if(G!=NULL)
    {
        void *elem=G->inserisci_elemento(5); // Richiama: F_inserisci_intero/float/carattere/stringa
        /* Verifica se e' presente un nodo con lo stesso nome nel grafo */
        int nodouguale = G->check_nodo_uguale(G,elem); // Richiama: F_check_nodo_uguale_lista/matrice

        if(nodouguale) {
            printf("Nodo ");
            G->stampa_elemento(elem);    // Richiama: F_stampa_intero/float/carattere/stringa
            printf(" gia' presente!\nSi prega di inserirne un altro.");
        }
        else {
            puts("Eseguo inserimento");
            G->inserisci_nodo(G,elem);  // Richiama: F_inserisci_nodo_lista/matrice
        }
    } else
        puts("Struttura non presente!\n");
}

/* Cancellazione di un arco */
void F_cancella_arco(Grafo G)
{
    G->stampa_generale(G); // Richiama: F_stampa_lista/matrice_adiacenza
    printf("\nSeleziona il primo nodo");
    int p=G->seleziona_nodo(G); // Richiama: F_seleziona_nodo_lista/matrice
    printf("\nSeleziona il secondo nodo");
    int a=G->seleziona_nodo(G);
    if(p >= G->nsize || a >= G->nsize || p==a) puts("\nIndici selezionati non validi!");
    else G->cancella_arco(G,p,a);   // Richiama: F_cancella_arco_lista/matrice
}

/* Cancellazione di un vertice */
void F_cancella_vertice(Grafo G)
{
    G->stampa_generale(G); // Richiama: F_stampa_lista/matrice_adiacenza
    printf("\nSeleziona il nodo da eliminare");
    int c=G->seleziona_nodo(G); // Richiama: F_seleziona_nodo_lista/matrice
    if(c >= G->nsize) puts("\nIndice selezionato non valido!");
    else G->cancella_nodo(G,c); // Richiama: F_cancella_nodo_lista/matrice
}

/* Calcolo del grafo trasposto */
void F_grafo_trasposto(Grafo G)
{
    if(G->struttura!=NULL)
        G->grafo_trasposto(G); // Richiama: F_trasposto_lista/matrice
    else puts("Struttura non presente!\n");
}

/* Generazione di un grafo casuale */
void F_grafo_casuale(Grafo G)
{
    int list_matr=-1,tipo_dato=-1,num_elem=-1,peso=-1;
    int scelta=F_scelta_grafo_casuale();

    G->dealloca_grafo(G->struttura,G); // Richiama: F_dealloca_grafo_lista/matrice

    if(scelta!=1) // Grafo random
    {
        /*
         * list_matr: 0=lista 1=matrice
         * tipo_dato: 1=int 2=float 3=carattere 4=stringa
         * num_elm: numero elementi grafo
         * peso: 1=pesato 2: non pesato
         * */

        /* Generazione casuale di lista/matrice e tipo di dato */
        list_matr=F_random_int_range(1,2);
        tipo_dato=F_random_int_range(1,5);
        num_elem=F_random_int_range(1,10);
        peso=F_random_int_range(1,2);
    } else // Grafo random con tipo scelto dall'utente
    {
        list_matr=F_list_matr();
        tipo_dato=F_tipo_dato_grafo();
        peso=F_grafo_pesato();
        num_elem=F_num_elem_grafo();
    }
    G=F_aggiungi_info(G,list_matr,tipo_dato,num_elem,peso); // inserimento di tutte le informazioni e callback per la gestione del grafo
    G=F_crea_grafo(G); // Creazione del grafo
}

/* Conversione di un grafo da lista a matrice e vicerversa */
void F_converti_grafo(Grafo G)
{
    if(G->struttura!=NULL)
        G->converti_grafo(G); // Richiama: F_lista_a_lista/matrice
    else
        puts("\nStruttura non presente!");
}

/* Prepara l'esecuzione della visita in ampiezza */
void F_visita_ampiezza(Grafo G)
{
    G->stampa_generale(G); // Richiama: F_stampa_lista/matrice_adiacenza
    int s=G->seleziona_nodo(G); // Richiama: F_seleziona_nodo_lista/matrice
    if(s > G->nsize) puts("Indice selezionato non valido!");
    else{
        void *Nodo_s=G->inizializza_bfsdfs(G,s,0); // Richiama: F_inizializza_bfsdfs_lista/matrice
        /* Inizializza_bfsdfs prende i seguenti parametri:
         * G: grafo corrente
         * s/0: nella BFS il nodo scelto. La DFS non ne necessita
         * 0/1: 0=BFS tutti i colori vengono inizializzati a bianco tranne il nodo scelto che diventa grigio
         *      1=DFS inizializza tutti i nodi con il colore bianco
         * */
        if(Nodo_s==NULL){puts("Error: inizializzazione per Bfs fallita!\b"); exit(-4);}
         F_inizializza_pred(G); // Inizializza il vettore dei predecessori
         printf("\nNodi raggiungibili dal nodo ");
         G->stampa_bfsdfs(G,Nodo_s); // Richiama: F_stampa_bfs_lista/matrice
         printf(" nella visita in ampiezza:\n");
         G->stampa_bfsdfs(G,Nodo_s);
         F_Bfs(G,Nodo_s); // BFS principale
         puts("\n");
    }
}

/* Prepara l'esecuzione della visita in profondita' */
void F_visita_profondita(Grafo G)
{
     void *Nodo_s=G->inizializza_bfsdfs(G,0,1); // Richiama: F_inizializza_bfsdfs_lista/matrice
     if(Nodo_s==NULL){puts("Error: inizializzazione per Bfs fallita!\b"); exit(-4);}
     F_inizializza_pred(G);  // Inizializza il vettore dei predecessori
     printf("\nStampa della visita in profondita':");
     F_Dfs(G); // pre-DFS Principale
}

/* Esecuzione della DFS */
void F_Dfs(Grafo G)
{
    G->verticedfs(G); // Richiama: F_verticeDfs_lista/matrice
}

/* DFS principale */
void F_Dfs_visit(Grafo G, void *u)
{
    /* Cambio del colore del nodo in grigio*/
    G->change_color(G,u,1); // Richiama: F_cambia_colore_bfs_lista/matrice (valore 1=grigio)
    /* Esegue la stampa del nodo corrente */
    G->stampa_bfsdfs(G,u);  // Richiama: F_stampa_bfs_lista/matrice
    puts("");

    /* Preleva un vertice adiacente, se presente, del nodo corrente */
    void *vAdiac=G->vertice_adiacente(G,u,NULL); // Richiama: F_vertice_adiacente_lista/matrice

    while (vAdiac!=NULL)
    {
        /* Prelevo il colore del vertice adiacente */
        int checkColor=G->check_color(G,vAdiac); // Richiama: F_controllo_colore_bfs_lista/matrice

        /* Verifica dell'esistenza di un ciclo */
        if(checkColor==1) G->ciclo=1;
        /* Verifica se il colore e' bianco (0) */
        if(checkColor==0)
        {
            /* Inserisce le informazioni nell'array dei predecessori (pred[vAdiac]=u) */
            G->predecessore_bfsdfs(G,u,vAdiac); // Richiama: F_predecessoreBfs_lista/matrice
            F_Dfs_visit(G,vAdiac);
        }
        vAdiac=G->vertice_adiacente(G,u,vAdiac); // Prelevo se presenti altri vertici adiacenti
    }
    G->change_color(G,u,2); // Modifico il colore del nodo in nero (2)
}

/* BFS principale */
void F_Bfs(Grafo G,void *s)
{
    Coda C=NULL;
    C=F_enqueue(C,s); // Metto in coda dell'elemento

    while (C!=NULL)
    {
        void *u=F_top_coda(C); // Ritorna il valore dell'elemento in testa

        void *vAdiac=G->vertice_adiacente(G,u,NULL); // Richiama: F_vertice_adiacente_lista/matrice
        /* vertice_adiacente prende come parametri:
         * G: grafo corrente
         * u: nodo in cui verificare la presente di adiacenti
         * vAdiac/NULL: l'ultimo nodo adiacente passato. La prima volta e' null
         * */

        while(vAdiac!=NULL)
        {
            int checkColor=G->check_color(G,vAdiac); // Verifico il colore

            if(checkColor==0) // Colore bianco
            {
                /* Cambio il colore, inserisco le info nell'array dei predecessori (pred[vAdiac]=u) e stmapo il nodo */
                G->change_color(G,vAdiac,1); // Cambio il colore in grigio (1)
                G->predecessore_bfsdfs(G,u,vAdiac); // Richiama: F_predecessoreBfs_lista/matrice
                G->stampa_bfsdfs(G,vAdiac); // Richiama: F_stampa_bfs_lista/matrice
                F_enqueue(C,vAdiac); // Inserisco l'adiacente in coda
            }
            vAdiac=G->vertice_adiacente(G,u,vAdiac); // Verifico se prensente un altro vertice adiacente
        }

        C=F_dequeue(C); // Rimuovo l'elemento in testa
        G->change_color(G,u,2); // Cambio il colore in nero (2)
    }
}

/* Preparazione per l'esecuzione della visita e la stampa del percorso */
void F_stampa_percorso(Grafo G)
{
    if(G->struttura!=NULL) {
        int ip=-1,ia=-1;
        /* Stampa del grafo per l'utente */
        G->stampa_generale(G); // Richiama: F_stampa_lista/matrice_adiacenza
        /* Selezione del nodo di partenza e arrivo */
        printf("\nSeleziona il nodo di partenza:");
        /* Selezione tramite indice e ricerca del nodo */
        ip=G->seleziona_nodo(G); // Richiama: F_seleziona_nodo_lista/matrice
        void *p = G->preleva_nodo(G,ip); // Richiama: F_preleva_nodo_lista
        printf("\nSelezione il nodo di arrivo:");
        ia=G->seleziona_nodo(G);
        void *a = G->preleva_nodo(G,ia);
        F_inizializza_pred(G); // Inizializza l'array dei predecessori

        /* Verifica dell'esistenza dei nodi e che siano diversi */
        if(p!=NULL && a!=NULL && ip!=ia)
        {
            int scelta=F_scelta_visita_grafo(); // Scelta del tipo di visita

            if(scelta==1) // BFS
            {
                p=G->inizializza_bfsdfs(G,ip,0); // Richiama: F_inizializza_bfsdfs_lista/matrice
                puts("\nStampa esecuzione BFS:");
                F_Bfs(G,p); // Esecuzione della visita dal nodo di partenza
                puts("\n\nStampa del percorso fra i due nodi scelti:");
                F_stampa_percorso_vertici(G,p,a); // Utilizzo d'array pred per mostrare il percorso minimo
            }
            else    // DFS
            {
                p=G->inizializza_bfsdfs(G,ip,1); // Richiama: F_inizializza_bfsdfs_lista/matrice
                puts("\nStampa esecuzione DFS:");
                F_Dfs_visit(G,p);   // Esecuzione della DFS principale
                puts("\n\nStampa del percorso fra i due nodi scelti:");
                F_stampa_percorso_vertici(G,p,a); // Stampa di uno dei possibili percorsi
            }
        }
        else
            puts("\nIndici selezionati non validi!");
        puts("\n");
    }
    else
        puts("Struttura non presente!\n");
}

/* Stampa il percorso tra due vertici (BFS=minimo, DFS=uno qualsiasi) */
void F_stampa_percorso_vertici(Grafo G, void *s,void *v)
{
    /* Verifica se si tratta dello stesso nodo */
    int confronto=G->confronto_elementi(s,v); // Richiama: F_confronto_interi/float/carattere/stringa

    if(confronto==0) // Stesso nodo
    {
        /* stampa del nodo */
        G->stampa_bfsdfs(G,s); // Richiama: F_stampa_bfs_lista/matrice
    } else
    {
        /* Prendo l'indice del nodo v */
        int i=G->indice_nodo(G,v); // Richiama: F_trova_indice_elem_lista/matrice

        /* Verifico che il nodo sia nullo o contiene un puntantore ad un nodo */
        void *predV=F_check_pred(G,i);

        if(predV==NULL) // Nessun cammino
        {
            printf("Non esiste nessun cammino tra ");
            G->stampa_bfsdfs(G,s);
            printf(" e ");
            G->stampa_bfsdfs(G,v);
            puts(".");
        }
        else
        {
            /* Procedo per il percorso */
            F_stampa_percorso_vertici(G,s,predV);
            G->stampa_bfsdfs(G,v);
        }
    }
}

/* Verifica dell'aciclicità del grafo */
void F_grafo_ciclo(Grafo G)
{
    void *Nodo_s=G->inizializza_bfsdfs(G,0,1); // Richiama: F_inizializza_bfsdfs_lista/matrice
    if(Nodo_s==NULL){puts("Error: inizializzazione per Bfs fallita!\b"); exit(-4);}
    F_inizializza_pred(G); // Inizializza l'array dei predecessori
    F_Dfs(G);   // Eseguo la DFS
    if(G->ciclo==1) puts("\nIl grafo contiene almeno un arco di ritorno. E' presente quindi un ciclo!!\n");
    else puts("\nIl grafo non contiene cicli!\nPotremmo trovare sicuramente un ordinamento topologico,"
                      " peccato che tale funzione non e' implementata...\n");
}