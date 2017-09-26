//
// Created by ika on 8/13/2017.
//

#ifndef INC_1_L_UTILITY_H
#define INC_1_L_UTILITY_H
#include "L_Grafo.h"
typedef void (*StampaElemento) (void*);
typedef  struct struttura_gestione_grafo *Grafo;
typedef struct struttura_grafo_lista_adiacenza *L;
typedef struct struttura_elemento_matrice *M;
typedef struct struttura_grafo_pesato *P;

void F_start();
int F_menu_principale();
int F_menu_avanzato(int listmatr);
Grafo F_info_grafo(Grafo G);
int F_list_matr();
int F_tipo_dato_grafo();
int F_num_elem_grafo();
int F_grafo_pesato();
Grafo F_aggiungi_info(Grafo G,int list_matr,int tipo_dato,int num_elem,int peso);
int F_seleziona(int dim,char minimo,char massimo,int escludi);
Grafo F_crea_matrice_adj(Grafo G);
Grafo F_crea_lista_adj(Grafo G);
void *F_crea_intero();
L F_alloca_elemento_lista(L Lista, void *elem);
void F_stampa_lista_adiacenza(Grafo G);
void F_stampa_intero(void *elem);
void F_inizializza_matrice(Grafo G);
void F_stampa_matrice_adiacenza(Grafo G);
void F_aggiungi_arco_lista(Grafo G,int p,int a);
void F_aggiungi_arco_matrice(Grafo G,int p,int a);
int F_seleziona_nodo_lista(Grafo G);
int F_seleziona_nodo_matrice(Grafo G);
int F_seleziona_indice(int dim, int nsize);
void * F_preleva_elem_lista(L lista,int elemento);
float F_inserisci_float(int dim);
P F_alloca_struttura_peso(float peso);
void F_stampa_peso_lista_adiacenza(Grafo G);
void F_stampa_peso_matrice_adiacenza(Grafo G);
int F_cambia_peso_lista(L elem,StampaElemento stampa_elemento);
int F_menu_scelta_cambio_peso();
void *F_inserisci_intero(int dim);
int F_check_nodo_uguale_lista(Grafo G,void *elem);
int F_check_nodo_uguale_matrice(Grafo G,void *elem);
int F_confronto_interi(void *stringa,void *stringa_nodo);
void F_inserisci_nodo_matrice(Grafo G,void *elem);
void F_inserisci_nodo_lista(Grafo G,void *elem);
void F_copia_matrice (float ** destmat, float ** srcmat,int dim);
void F_cancella_arco_lista(Grafo G,int p,int a);
void F_cancella_arco_matrice(Grafo G,int p,int a);
void F_dealloca_intero(void *elem);
void F_cancella_nodo_matrice(Grafo G,int c);
void F_cancella_nodo_lista(Grafo G,int c);
float F_ritorna_negativo(float num);
void F_trasposto_matrice(Grafo G);
void F_trasposto_lista(Grafo G);
void *F_copia_dato_intero(void *val);
void F_copia_matrice_identica (float ** destmat, float ** srcmat,int dim);
void F_dealloca_grafo_lista(L Lista,Grafo G);

#endif //INC_1_L_UTILITY_H
