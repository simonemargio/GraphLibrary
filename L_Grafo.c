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