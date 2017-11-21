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
typedef void *(*InserisciElemento) (int);
typedef int (*CheckNodoUguale) (Grafo G,void*);
typedef int (*ConfrontoElementi) (void*, void*);
typedef void (*InserisciNodo) (Grafo G,void*);
typedef void (*CancellaArco) (Grafo G,int,int);
typedef void (*DeallocaElemento) (void*);
typedef void  (*CancellaNodo) (Grafo G,int);
typedef void (*GrafoTrasposto) (Grafo G);
typedef void *(*CopiaDato) (void *);
typedef void (*DeallocaGrafo) (void *,Grafo G);
typedef void (*ConvertiGrafo) (Grafo G);
typedef void *(*InizialiazzaBfs) (Grafo G,int s);
typedef void *(*VerticeAdiacente) (Grafo G,void *u,void *ultimo);
typedef int (*CheckColorBfs) (Grafo G,void *);
typedef void (*ChangeColorBdfs) (Grafo G,void *,int colore);
typedef void (*StampaBfs) (Grafo G,void *);
typedef void (*PredecessoreBfs) (Grafo G,void *,void *);

//typedef void (*PercorsoVertici) (Grafo G,void *,void *);
typedef void *(*PrelevaNodo) (Grafo G,int i);
typedef int (*SelezionaIndiceNodo) (Grafo G, void *);


struct struttura_gestione_grafo
{
    void *struttura;
    int nsize;
    int infpeso;
    int listmatr;
    int tipodato;

    TipoStruttura tipo_struttura;
    TipoElemento tipo_elemento;
    StampaElemento stampa_elemento;
    InserisciArco inserisci_arco;
    SelezionaNodo seleziona_nodo;
    StampaGenerale stampa_generale;
    InserisciElemento inserisci_elemento;
    CheckNodoUguale check_nodo_uguale;
    ConfrontoElementi confronto_elementi;
    InserisciNodo inserisci_nodo;
    CancellaArco cancella_arco;
    DeallocaElemento dealloca_elemento;
    CancellaNodo cancella_nodo;
    GrafoTrasposto grafo_trasposto;
    CopiaDato copia_dato;
    DeallocaGrafo  dealloca_grafo;
    ConvertiGrafo converti_grafo;
    InizialiazzaBfs inizializza_bfs;
    VerticeAdiacente vertice_adiacente;
    CheckColorBfs check_color;
    ChangeColorBdfs change_color;
    StampaBfs stampa_bfs;
    PredecessoreBfs predecessore_bfs;
    SelezionaIndiceNodo indice_nodo;

    PrelevaNodo preleva_nodo;
    struct struttura_elemento_array_pred *pred;
};

struct struttura_elemento_array_pred
{
    void *nodo;
};

struct struttura_grafo_lista_adiacenza
{
    void *nodo;
    void *extra; // qui usato per colore
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
    void *extra;
   // struct struttura_grafo_pesato *ptrPeso;
};

struct struttra_extra_colore
{
    int colore; // 0: bianco 1: grigio 2: nero
};

typedef struct struttura_grafo_lista_adiacenza *L;
typedef struct struttura_elemento_matrice *M;
typedef struct struttura_elemento_array_nodo_matrice *Nm;
typedef struct struttura_grafo_pesato *P;
typedef struct struttra_extra_colore *C;
typedef struct struttura_elemento_array_pred *Pred;

Grafo F_alloca_grafo(Grafo G);
Grafo F_crea_grafo(Grafo G);
void F_aggiungi_arco(Grafo G);
void F_aggiungi_vertice(Grafo G);
void F_cancella_arco(Grafo G);
void F_cancella_vertice(Grafo G);
void F_grafo_trasposto(Grafo G);
void F_grafo_casuale(Grafo G);
void F_converti_grafo(Grafo G);
void F_visita_ampiezza(Grafo G);
void F_Bfs(Grafo G,void *s);
void F_stampa_percorso_vertici(Grafo G, void *s,void *p);
void F_stampa_percorso(Grafo G);


#endif //INC_1_L_GRAFO_H
