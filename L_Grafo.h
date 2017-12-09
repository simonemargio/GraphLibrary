#ifndef INC_1_L_GRAFO_H
#define INC_1_L_GRAFO_H

#include <stdio.h>
#include "L_Utility.h"

/* Struttura principale contenente callback e la rappresentazione del grafo (lista/matrice) */
typedef struct struttura_gestione_grafo *Grafo;

/* Callback */
typedef Grafo (*TipoStruttura) (Grafo G);           // Gestione della creazione della struttura principale (lista/matrice)
typedef void *(*TipoElemento) (void);               // Gestione del tipo di dato presente nel grafo
typedef void (*StampaElemento) (void*);             // Stampa del tipo di un elemento
typedef void (*InserisciArco) (Grafo G,int,int);    // Gestione dell'iserimento di un arco
typedef int (*SelezionaNodo) (Grafo G);             // Selezione di un nodo scelto
typedef void (*StampaGenerale) (Grafo G);           // Stampa generica del grafo
typedef void *(*InserisciElemento) (int);           // Richiesta all'utente di inserire un valore per il grafo
typedef int (*CheckNodoUguale) (Grafo G,void*);     // Verifica dell'esistenza di un nodo con "nome" identico a quello che si vuole inserire
typedef int (*ConfrontoElementi) (void*, void*);    // Confronto di due valori presenti nei nodi
typedef void (*InserisciNodo) (Grafo G,void*);      // Inserimento di un nuovo nodo
typedef void (*CancellaArco) (Grafo G,int,int);     // Eliminazione di un arco
typedef void (*DeallocaElemento) (void*);           // Deallocazione del tipo di un elemento
typedef void  (*CancellaNodo) (Grafo G,int);        // Eliminazione di un nodo
typedef void (*GrafoTrasposto) (Grafo G);           // Gestisce il trasposto del grafo
typedef void *(*CopiaDato) (void *);                // Copia il dato di un nodo (memcpy)
typedef void (*DeallocaGrafo) (void *,Grafo G);     // Eliminazione del grafo
typedef void (*ConvertiGrafo) (Grafo G);            // Gestione del passaggio dalle due rappresentazioni del grafo
typedef void *(*InizialiazzaBfsDfs) (Grafo G,int s,int df); // Inizializza l'array dei colori prima della visita
typedef void *(*VerticeAdiacente) (Grafo G,void *u,void *ultimo);   // Ritorna, se presente, un vertice adiacente dal nodo passato
typedef int (*CheckColorBfs) (Grafo G,void *);                      // Verifica del colore di un nodo
typedef void (*ChangeColorBdfs) (Grafo G,void *,int colore);        // Cambia il colore di un nodo
typedef void (*StampaBfsDfs) (Grafo G,void *);                      // Stampa del nodo (usato da BFS/DSF)
typedef void (*PredecessoreBfsDfs) (Grafo G,void *,void *);         // Gestione dell'array dei predecessori
typedef void *(*PrelevaNodo) (Grafo G,int i);                       // Ritorna il puntatore del nodo scelto in base all'indice dato
typedef int (*SelezionaIndiceNodo) (Grafo G, void *);               // Ritorna l'indice numerico del nodo in base al dato
typedef void (*VerticeDfs) (Grafo G);                               // Funzione di visita in profondita' (richiama DFS_VISIT)
typedef void(*SalvaElemGrafo) (FILE *,void *);                      // Gestisce le funzioni di input/output da file del grafo

/* Struttura principale */
struct struttura_gestione_grafo
{
    void *struttura;    // Punta alla rappresentazione scelta del grafo: lista o matrice
    int nsize;          // Numero totale di elementi
    int infpeso;        // 1=Pesato - 2=Non pesato
    int listmatr;       // 1=Lista Adj - 2=Matrice Adj
    int tipodato;       // 1=Int - 2=Float - 3=Char - 4=Stringa
    int ciclo;          // 0=No ciclo - 1=Ciclo presente

    /* Commenti e definizioni in alto */
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
    InizialiazzaBfsDfs inizializza_bfsdfs;
    VerticeAdiacente vertice_adiacente;
    CheckColorBfs check_color;
    ChangeColorBdfs change_color;
    StampaBfsDfs stampa_bfsdfs;
    PredecessoreBfsDfs predecessore_bfsdfs;
    SelezionaIndiceNodo indice_nodo;
    PrelevaNodo preleva_nodo;
    VerticeDfs verticedfs;
    SalvaElemGrafo salvaelemgrafo;
    struct struttura_elemento_array_pred *pred; // Array dei predecessori
};

/* Singolo elemento dell'array dei predecessori */
struct struttura_elemento_array_pred
{
    void *nodo;
};

/* Grafo in rappresentazione in lista di Adj */
struct struttura_grafo_lista_adiacenza
{
    void *nodo; // Puntatore al nodo
    void *extra;
    /* Info su extra:
     * Il puntatore void viene usato per permettere di collegare
     * ad ogni singolo nodo un'informazione che puo' essere utile
     * per svolgere determinate funzioni. In caso serva un'associazione
     * uno ad uno tra l'informazione e il nodo si puo' utilizzare tale
     * puntatore.
     * In questo caso esso viene usato per collegare la struttura che
     * porta l'informazione del colore del nodo
     * */
    struct struttura_grafo_pesato *ptrPeso; // Puntatore al peso se presente
    struct struttura_grafo_lista_adiacenza *ptrArco; // Puntatore al nodo successivo
    struct struttura_grafo_lista_adiacenza *ptrNext; // Puntatore al nodo collegato da un arco
};

/* Mantiene l'informazione del peso di un arco */
struct struttura_grafo_pesato
{
    float peso;
};

/* Grafo in rappresentazione in matrice di Adj */
struct struttura_elemento_matrice
{
    void *nodo; // Puntatore all'array contenenti i nodi del grafo
    float **matrice; // Puntatore alla matrice
    /* Info su matrice:
     * La matrice e' espressa nel tipo float in quanto
     * nei grafi pesati la cella della matrice contiene il peso.
     * Caso opposto un valore diverso da zero.
     * */
};

/* Contiene l'informazione sui nodi del grefo nella rappresentazione a matrice */
struct struttura_elemento_array_nodo_matrice
{
    void *nodo;
    void *extra; // Spiegato in struttura_grafo_lista_adiacenza
};

/* Informazione sul colore */
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

Grafo F_alloca_grafo(Grafo G);       // Funzione per l'allocazione della struttura principale per la gestione del grafo
Grafo F_crea_grafo(Grafo G);         // Funzione per la creazione della struttura grafo
void F_aggiungi_arco(Grafo G);       // Aggiunta di un arco al grafo
void F_aggiungi_vertice(Grafo G);    // Aggiunge un nuovo vertice al grafo
void F_cancella_arco(Grafo G);       // Cancellazione di un arco
void F_cancella_vertice(Grafo G);    // Cancelllazione di un vertice
void F_grafo_trasposto(Grafo G);     // Calcolo del grafo trasposto
void F_grafo_casuale(Grafo G);       // Generazione di un grafo casuale
void F_converti_grafo(Grafo G);      // Conversione di un grafo da lista a matrice e vicerversa
void F_visita_ampiezza(Grafo G);     // Prepara l'esecuzione della visita in ampiezza
void F_Bfs(Grafo G,void *s);         // BFS principale
void F_stampa_percorso(Grafo G);     // Preparazione per l'esecuzione della visita e la stampa del percorso
void F_visita_profondita(Grafo G);   // Prepara l'esecuzione della visita in profondita'
void F_Dfs(Grafo G);                 // Esecuzione della DFS
void F_Dfs_visit(Grafo G, void *u);  // DFS principale
void F_grafo_ciclo(Grafo G);         // Verifica dell'aciclicità del grafo
void F_stampa_percorso_vertici(Grafo G, void *s,void *p); // Stampa il percorso tra due vertici (BFS=minimo, DFS=uno qualsiasi)

#endif //INC_1_L_GRAFO_H
