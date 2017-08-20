//
// Created by ika on 8/13/2017.
//

#ifndef INC_1_L_GRAFO_H
#define INC_1_L_GRAFO_H
#include "L_Utility.h"

typedef struct struttura_gestione_grafo *Grafo;
typedef Grafo (*TipoStruttura) (Grafo G);
typedef void *(*TipoElemento) (void);
typedef void (*StampaElemento) (void*);
typedef void (*InserisciArco) (Grafo G,int,int);
typedef int (*SelezionaNodo) (Grafo G);
typedef void (*StampaGenerale) (Grafo G);

struct struttura_gestione_grafo
{
    void *struttura;
    int nsize;
    int infpeso;
    int listmatr;

    TipoStruttura tipo_struttura;
    TipoElemento tipo_elemento;
    StampaElemento stampa_elemento;
    InserisciArco inserisci_arco;
    SelezionaNodo seleziona_nodo;
    StampaGenerale stampa_generale;
};


struct struttura_grafo_lista_adiacenza
{
    void *nodo;
    struct struttura_grafo_pesato *ptrPeso;
    struct struttura_grafo_lista_adiacenza *ptrArco;
    struct struttura_grafo_lista_adiacenza *ptrNext;
};

struct struttura_grafo_pesato
{
    float peso;
};


struct struttura_elemento_matrice
{
    void *nodo;
    float **matrice; // Matrice + peso
};

struct struttura_elemento_array_nodo_matrice
{
    void *nodo;
   // struct struttura_grafo_pesato *ptrPeso;
};

typedef struct struttura_grafo_lista_adiacenza *L;
typedef struct struttura_elemento_matrice *M;
typedef struct struttura_elemento_array_nodo_matrice *Nm;
typedef struct struttura_grafo_pesato *P;

Grafo F_alloca_grafo(Grafo G);
Grafo F_crea_grafo(Grafo G);
void F_aggiungi_arco(Grafo G);


#endif //INC_1_L_GRAFO_H
