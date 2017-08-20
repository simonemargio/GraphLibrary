//
// Created by ika on 8/13/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include "L_Utility.h"



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
        printf("\nINDICE PARTENZA: %d INDICE ARRIVO: %d SIZE: %d\n",p,a,G->nsize);
        if(p >= G->nsize || a >= G->nsize || p==a) puts("\nIndici selezionati non validi!");
        else G->inserisci_arco(G,p,a);
    }
    else
        puts("Struttura non presente!\n");

    return;
}





