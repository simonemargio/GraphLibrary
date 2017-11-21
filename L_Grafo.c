//
// Created by ika on 8/13/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include "L_Utility.h"
#include "L_Stack.h"
#include "L_Coda.h"


Grafo F_alloca_grafo(Grafo G)
{
    G = (struct struttura_gestione_grafo *) malloc (sizeof(struct struttura_gestione_grafo));

    return G;
}



Grafo F_crea_grafo(Grafo G)
{
    if(G!=NULL) G=G->tipo_struttura(G);
    else
    {
        puts("\nError: stuttura non presente!\n");
        exit (-1);
    }
    return  G;
}

void F_aggiungi_arco(Grafo G)
{
    if(G!=NULL)
    {
        G->stampa_generale(G);
        printf("\nSeleziona il nodo di partenza");
        int p=G->seleziona_nodo(G);
        printf("\nSeleziona il nodo d'arrivo");
        int a=G->seleziona_nodo(G);
        if(p >= G->nsize || a >= G->nsize || p==a) puts("\nIndici selezionati non validi!");
        else G->inserisci_arco(G,p,a);
    }
    else
        puts("Struttura non presente!\n");
}

void F_aggiungi_vertice(Grafo G)
{
    if(G!=NULL)
    {
        void *elem=G->inserisci_elemento(5);
        int nodouguale = G->check_nodo_uguale(G,elem);

        if(nodouguale) {
            printf("Nodo ");
            G->stampa_elemento(elem);
            printf(" gia' presente!\nSi prega di inserirne un altro.");
        }
        else {
            puts("Eseguo inserimento");
            G->inserisci_nodo(G,elem);
        }
    } else
        puts("Struttura non presente!\n");
}

void F_cancella_arco(Grafo G)
{
    G->stampa_generale(G);
    printf("\nSeleziona il primo nodo");
    int p=G->seleziona_nodo(G);
    printf("\nSeleziona il secondo nodo");
    int a=G->seleziona_nodo(G);
    if(p >= G->nsize || a >= G->nsize || p==a) puts("\nIndici selezionati non validi!");
    else G->cancella_arco(G,p,a);
}

void F_cancella_vertice(Grafo G)
{
    G->stampa_generale(G);
    printf("\nSeleziona il nodo da eliminare");
    int c=G->seleziona_nodo(G);
    if(c >= G->nsize) puts("\nIndice selezionato non valido!");
    else G->cancella_nodo(G,c);
}

void F_grafo_trasposto(Grafo G)
{
    if(G->struttura!=NULL)
        G->grafo_trasposto(G);
    else puts("Struttura non presente!\n");
}

void F_grafo_casuale(Grafo G)
{
    int list_matr=-1,tipo_dato=-1,num_elem=-1,peso=-1;
    int scelta=F_scelta_grafo_casuale();

    G->dealloca_grafo(G->struttura,G);

    if(scelta!=1) // Grafo random
    {
        list_matr=F_random_int_range(1,2);
        tipo_dato=F_random_int_range(1,5);

        printf("\nCome dato ho scelto: %d. Metto 1",tipo_dato); // Cancella
        tipo_dato=1; // Cancella

        num_elem=F_random_int_range(1,10);
        peso=F_random_int_range(1,2);
    } else // Grafo random utente
    {
        list_matr=F_list_matr();
        tipo_dato=F_tipo_dato_grafo();
        peso=F_grafo_pesato();
        num_elem=F_num_elem_grafo();
    }
    G=F_aggiungi_info(G,list_matr,tipo_dato,num_elem,peso);
    G=F_crea_grafo(G);
}

void F_converti_grafo(Grafo G)
{
    if(G->struttura!=NULL)
        G->converti_grafo(G);
    else
        puts("\nStruttura non presente!");
}

void F_visita_ampiezza(Grafo G)
{
    G->stampa_generale(G);
    int s=G->seleziona_nodo(G);
    if(s > G->nsize) puts("Indice selezionato non valido!");
    else{
        void *Nodo_s=G->inizializza_bfs(G,s);
        if(Nodo_s==NULL){puts("Error: inizializzazione per Bfs fallita!\b"); exit(-4);}
         F_inizializza_pred(G);
         printf("\nNodi raggiungibili dal nodo ");
         G->stampa_bfs(G,Nodo_s);
         printf(" nella visita in ampiezza:\n");
         G->stampa_bfs(G,Nodo_s);
         F_Bfs(G,Nodo_s);
         puts("\n");
    }
}

void F_Bfs(Grafo G,void *s)
{
    Coda C=NULL;
    C=F_enqueue(C,s);

    while (C!=NULL)
    {
        void *u=F_top_coda(C);
       // if(u==NULL) puts("\n u nullo");
       // else {L aa=u; printf("\nprelevato u: |%d|\n\n",*((int *)aa->nodo));}

        void *vAdiac=G->vertice_adiacente(G,u,NULL);

        while(vAdiac!=NULL)
        {
            // CANC
         //   L bb=vAdiac; printf("\nHo preso un adiacente: |%d|\n\n",*((int *)bb->nodo));

            int checkColor=G->check_color(G,vAdiac);
          //  puts("\nControllato il colore");
            if(checkColor==0) // bianco
            {
                //puts("\nColore bianco\n");
                G->change_color(G,vAdiac,1); // metto grigio
                G->predecessore_bfs(G,u,vAdiac);
                G->stampa_bfs(G,vAdiac);
                F_enqueue(C,vAdiac);
            }
            //else puts("\nIl colore non e' bianco\n");

            vAdiac=G->vertice_adiacente(G,u,vAdiac);
        }

        C=F_dequeue(C);
       // puts("\n2");
        G->change_color(G,u,2);
       // puts("\n3");
    }
}

void F_stampa_percorso(Grafo G)
{
    if(G->struttura!=NULL) {
        int ip=-1,ia=-1;
        G->stampa_generale(G);
        printf("\nSeleziona il nodo di partenza:");
        ip=G->seleziona_nodo(G);
        void *p = G->preleva_nodo(G,ip);
        printf("\nSelezione il nodo di arrivo:");
        ia=G->seleziona_nodo(G);
        void *a = G->preleva_nodo(G,ia);
        F_inizializza_pred(G);

      //  L pp=p, aa=a; // Canc
      //  printf("\nHo preso i nodi |%d| e |%d|\n",*((int *)pp->nodo), *((int *)aa->nodo)); // Canc

        if(p!=NULL && a!=NULL)
        {
            int scelta=F_scelta_visita_grafo();
           // int scelta=1;
            puts("\nStampa del percorso fra i due nodi scelti:");
            if(scelta==1) // BFS
            {
                p=G->inizializza_bfs(G,ip);

              //  pp=p;   // Canc
              //  printf("\n\nIl nodo di partenza e' |%d|\n\n",*((int *)pp->nodo)); // Canc

                F_Bfs(G,p);

                /*
                int k=0;
                Pred arr=G->pred;

                for(k=0;k<G->nsize;k++)
                {
                    if(arr[k].nodo==NULL)
                        puts("\n||->VUOTO");
                    else
                        puts("\n||->QUALCOSA");
                }*/
                F_stampa_percorso_vertici(G,p,a);

            }
            else
            {
                // Esegui DFS
                F_stampa_percorso_vertici(G,p,a);
            }
        }
        else
            puts("\nIndici selezionati non validi!");

        // prendo i nodo s e nodo arrivo
        // controllo l'esistenza dei nodi
        // Mostro menu su quale visita effettuare
        // Chiamo call che passa grafo e due void che sono i vertici

        puts("\n");
    }
    else
        puts("Struttura non presente!\n");
}

void F_stampa_percorso_vertici(Grafo G, void *s,void *v)
{
    int confronto=G->confronto_elementi(s,v);

    //L ss=s, vv=v;
   // printf("\n\nCONF |%d| con |%d|\n\n",*((int *)ss->nodo),*((int *)vv->nodo) );

    if(confronto==0)
    {
      //  puts("\n\n\nSTAMPO\n\n\n");
      //  G->stampa_elemento(ss->nodo);
         G->stampa_bfs(G,s);
    } else
    {
        int i=G->indice_nodo(G,v);
      //  printf("\nINDICE V |%d|\n",i);
        void *predV=F_check_pred(G,i);

        if(predV==NULL)
        {
            printf("Non esiste nessun cammino tra ");
            G->stampa_bfs(G,s);
            printf(" e ");
            G->stampa_bfs(G,v);
            puts(".");
        }
        else
        {
            F_stampa_percorso_vertici(G,s,predV);
            G->stampa_bfs(G,v);
        }
    }

}