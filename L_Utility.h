#ifndef INC_1_L_UTILITY_H
#define INC_1_L_UTILITY_H
#include "L_Grafo.h"

typedef void (*StampaElemento) (void*);             // Call per la stampa di un elemento
typedef  struct struttura_gestione_grafo *Grafo;    // Struttura principale di gestione del grafo
typedef struct struttura_grafo_lista_adiacenza *L;  // Struttura del grafo in lista di Adj
typedef struct struttura_elemento_matrice *M;       // Struttura contenente la matrice di Adj
typedef struct struttura_grafo_pesato *P;           // Struttura contenente l'informazione sul peso
typedef struct struttura_elemento_array_nodo_matrice *Nm; // Struttura contenente i nodi relativi alla matrice di Adj
typedef struct struttra_extra_colore *C;            // Struttura per il mantenimento dell'informazione colore per le visite

void F_start();                         // Funzione principale
int F_menu_principale();                // Funzione di stampa del menu' principale
int F_menu_avanzato(int listmatr);      // Funzione di stampa del secondo menu'
Grafo F_info_grafo(Grafo G);            // Funzione per l'inserimento delle proprieta' del grafo
int F_list_matr();                      // Richiesta del tipo di grafo da usare
int F_tipo_dato_grafo();                // Richiesta del tipo di dato contenuto nel grafo
int F_num_elem_grafo();                 // Richiesta del numero di elementi del grafo
int F_grafo_pesato();                   // Richiesta dell'aggiunta del peso al grafo
Grafo F_aggiungi_info(Grafo G,int list_matr,int tipo_dato,int num_elem,int peso); // Funzione di inserimento di tutte le informazioni e callback per la gestione del grafo
int F_seleziona(int dim,char minimo,char massimo,int escludi);
Grafo F_crea_matrice_adj(Grafo G);      // Funzione per la creazione della struttura principale di tipo lista di Adj
Grafo F_crea_lista_adj(Grafo G);        // Creazione della lista di Adj

L F_alloca_elemento_lista(L Lista, void *elem);     // Creazione di un elemento della lista di Adj
void F_stampa_lista_adiacenza(Grafo G);             // Funzione di stampa generica della lista di Adj

void F_inizializza_matrice(Grafo G);                // Funzione di inizializzazione della matrice
void F_stampa_matrice_adiacenza(Grafo G);
void F_aggiungi_arco_lista(Grafo G,int p,int a);    // Aggiunta di un arco in una lista di Adj
void F_aggiungi_arco_matrice(Grafo G,int p,int a);  // Aggiunta di un arco in una matrice di Adj
int F_seleziona_nodo_lista(Grafo G);                // Richiesta all'utente di selezionare un nodo della lista di Adj
int F_seleziona_nodo_matrice(Grafo G);              // Richiesta all'utente di selezionare un nodo della matrice di Adj
int F_seleziona_indice(int dim, int nsize);         // Funzione che richiede all'utente di inserire l'indice del nodo su cui effettuare le operazioni
void * F_preleva_elem_lista(L lista,int elemento);  // Seleziona un nodo della lista di Adj in base all'indice passato

P F_alloca_struttura_peso(float peso);                           // Alloca la struttura per gestire il peso di un arco
void F_stampa_peso_lista_adiacenza(Grafo G);                     // Stampa il peso di un grafo in lista di Adj
void F_stampa_peso_matrice_adiacenza(Grafo G);                   // Stampa il peso di un grafo in una matrice di Adj
int F_cambia_peso_lista(L elem,StampaElemento stampa_elemento);  // Permette all'utente di cambiare il peso di un nodo gia' presente
int F_menu_scelta_cambio_peso();                                 // Menu' di scelta per il cambio del peso di un arco

int F_check_nodo_uguale_lista(Grafo G,void *elem);               // Verifica se e' gia' presente un nodo con il medesimo dato nella lista di Adj
int F_check_nodo_uguale_matrice(Grafo G,void *elem);             // Verifica se e' gia' presente un nodo con il medesimo dato nella matrice di Adj

void F_inserisci_nodo_matrice(Grafo G,void *elem);                // Inserimento di un nuovo nodo in una matrice di Adj
void F_inserisci_nodo_lista(Grafo G,void *elem);                  // Inserimento di un nuovo nodo in una lista di Adj
void F_copia_matrice (float ** destmat, float ** srcmat,int dim); // Inizializza la nuova matrice e ne copia le informazioni degli archi dalla vecchia
void F_cancella_arco_lista(Grafo G,int p,int a);                  // Eliminazione di un arco nella lista di Adj
void F_cancella_arco_matrice(Grafo G,int p,int a);                // Eliminazione di un arco nella matrice di Adj

void F_cancella_nodo_matrice(Grafo G,int c);    // Cancella un nodo della matrice di Adj
void F_cancella_nodo_lista(Grafo G,int c);      // Cancella un nodo della lista di Adj
float F_ritorna_negativo(float num);            // Ritorno il valore float in negativo
void F_trasposto_matrice(Grafo G);              // Effettua il trasposto della matrice di Adj
void F_trasposto_lista(Grafo G);                // Effettua il trasposto della lista di Adj

void F_copia_matrice_identica (float ** destmat, float ** srcmat,int dim);  // Inizializza la nuova matrice e ne copia le informazioni degli archi dalla vecchia (usata per il trasposto)
void F_dealloca_grafo_lista(void *struttura,Grafo G);                       // Deallocazione del grafo in lista di Adj
void F_dealloca_grafo_matrice(void *struttura,Grafo G);                     // Deallocazione del grafo in matrice di Adj
int F_scelta_grafo_casuale();                                               // Richiesta del tipo di grafo da generare
int F_random_int_range(int min, int max);                                   // Genera un valore intero random
void F_lista_a_matrice(Grafo G);                                            // Trasforma la lista in matrice di Adj
void F_matrice_a_lista(Grafo G);                                            // Trasforma la matrice in lista di Adj

void *F_inizializza_bfsdfs_lista(Grafo G,int s,int df);                     // Funzione di inizializzazione dell'array colore per lista prima delle visite
void *F_inizializza_bfsdfs_matrice(Grafo G,int s,int df);                   // Funzione di inizializzazione dell'array colore per matrice prima delle visite
void *F_vertice_adiacente_lista(Grafo G,void *u, void *ultimo);             // Ritorna il vertice adiacente, se presente, in una lista di Adj
void *F_vertice_adiacente_matrice(Grafo G,void *u, void *ultimo);           // Ritorna il vertice adiacente, se presente, in una matrice di Adj
int F_controllo_colore_bfs_lista(Grafo G, void *elem);                      // Funzione per la verifica del colore di un nodo (lista)
int F_controllo_colore_bfs_matrice(Grafo G, void *elem);                    // Funzione per la verifica del colore di un nodo (matrice)
void F_cambia_colore_bfs_lista(Grafo G,void *elem, int colore);             // Cambia il colore del nodo con il valore passato (lista)
void F_cambia_colore_bfs_matrice(Grafo G,void *elem, int colore);           // Cambia il colore del nodo con il valore passato (matrice)
L F_trova_elemento_bfs_lista(Grafo G, void *elem);                          // Ritorna il nodo della struttura principale in lista di Adj
void F_stampa_bfs_lista(Grafo G,void *elem);                                // Stampa generica per BFS
void F_stampa_bfs_matrice(Grafo G,void *elem);                              // Stampa BFS per matrice
void* F_trova_elemento_bfs_matrice(Grafo G, void *elem);                    // Ritorna il nodo della struttura principale in matrice di Adj

/*
 * Funzioni di gestioni del tipo di dato presente nel grafo
 *
 * F_crea_: generazione di un valore casuale del tipo specificato
 * F_stampa_: stampa del valore
 * F_confronto_: confronto di due valori del medesimo tipo
 * F_dealloca_: deallocazione del tipo specidicato
 * F_copia_dato_: copia del valore (memcpy)
 *
 * */
/* Intero */
void *F_crea_intero();
void F_stampa_intero(void *elem);
void *F_inserisci_intero(int dim);
int F_confronto_interi(void *stringa,void *stringa_nodo);
void F_dealloca_intero(void *elem);
void *F_copia_dato_intero(void *val);
/* Float */
void *F_crea_float();
void F_stampa_float(void *elem);
void * F_inserisci_float(int dim);
int F_confronto_float(void *stringa,void *stringa_nodo);
void F_dealloca_float(void *elem);
void *F_copia_dato_float(void *val);
/* Carattere */
void *F_crea_carattere();
void F_stampa_carattere(void *elem);
void *F_inserisci_carattere(int dim);
int F_confronto_carattere(void *stringa, void *stringa_nodo);
void F_dealloca_carattere_stringa(void *elem);
void *F_copia_dato_carattere(void *val);
/* Stringa */
void *F_crea_stringa();
void F_stampa_stringa(void *elem);
void *F_inserisci_stringa(int dim);
int F_confronto_stringa(void *stringa, void *stringa_nodo);
void *F_copia_dato_stringa(void *val);


void F_inizializza_pred(Grafo G);                        // Inizializza l'array dei predecerssori
void F_predecessoreBfs_lista(Grafo G, void *,void *);    // Gestione del'array dei predecessori per lista Adj
void F_predecessoreBfs_matrice(Grafo G,void *,void *);   // Gestione del'array dei predecessori per matrice Adj

void *F_preleva_nodo_lista(Grafo G, int i);              // Ritorna un nodo della lista in base all'indice passato
void *F_preleva_nodo_matrice(Grafo G, int i);            // Ritorna un nodo della matrice in base all'indice passato
int F_scelta_visita_grafo();                             // Richiesta del tipo di visita da effetturare
void *F_check_pred(Grafo G,int i);                       // Ritorna il nodo presente nell'array

int F_trova_indice_elem_lista(Grafo G,void *elem);       // Ritorna l'indice dell'elemento passato in una lista di Adj
int F_trova_indice_elem_matrice(Grafo G,void *elem);     // Ritorna l'indice dell'elemento passato in una matrice di Adj

void F_verticeDfs_lista(Grafo G);                   // DFS: lista
void F_verticeDfs_matrice(Grafo G);                 // DFS: matrice
int F_menu_leggi_scrivi_file();                     // Funzione di stampa per la gestione di un grafo da file
Grafo F_leggi_scrivi_grafo(Grafo G); // Funzione per la lettura o scrittura di un grafo da file

#endif //INC_1_L_UTILITY_H
