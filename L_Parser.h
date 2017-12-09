//
// Created by ikaros on 23/11/2017.
//

#ifndef INC_5_ESERCIZIO_5_GRAFI_L_PARSER_H
#define INC_5_ESERCIZIO_5_GRAFI_L_PARSER_H

#include <stdio.h>

/* Struttura principale di gestione del grafo e delle relative callback */
typedef  struct struttura_gestione_grafo *Grafo;

void F_salva_grafo(Grafo G);                      // Funzione per salvare le informazioni di un grafo su file
void F_salva_info(FILE *fd,Grafo G,int listmatr); // Funzione per il salvataggio su file delle info del grafo
void F_salva_elem_nodi(FILE *fd,Grafo G);         // Salvataggio su file di tutti i nodi
void F_salva_elem_int(FILE *fd,void *el);         // Salvataggio su file di un tipo intero
void F_salva_elem_char(FILE *fd,void *el);        // Salvataggio su file di un tipo carattere
void F_salva_elem_string(FILE *fd,void *el);      // Salvataggio su file di un tipo stringa
void F_salva_elem_float(FILE *fd,void *el);       // Salvataggio su file di un tipo float
void F_salva_archi(FILE *fd,Grafo G);             // Salvataggio dell'informazione relativa ai nodi con i relativi archi e pesi
Grafo F_leggi_grafo(Grafo Old);                   // Funzione principale di lettura del grafo da file
char *F_alloca_vett_lettura();                    // Array usato per contenere i caratteri letti
void F_inserisci_info_grafo(Grafo G,FILE *fd,char *arr);           // Funzione principale per la lettura della prima riga da file
int F_leggi_prima_riga(FILE *fd,char *arr);                        // Esegue la lettura di un elemento della prima riga da file
void F_inizializza_array(char *arr);                               // Inizializzazione dell'array di lettura caratteri
void F_alloca_lista(Grafo G, FILE *fd,char *arr, L lis);           // Funzione principale per la lettura della seconda riga da file
void F_lettura_vertice(Grafo G, FILE *fd,char *arr, L lis);        // Esegue la lettura di tutti i vertici nella seconda riga
void F_esegui_lettura_vertice(Grafo G, FILE *fd,char *arr, L lis); // Legge da file un vertice
void F_alloca_nodo(Grafo G,FILE *fd,char *arr);                    // Inizia la lettura della terza riga del file contenente info su nodi e archi
void F_lettura_vertice_arco(Grafo G,FILE *fd,char *arr);            // Provvede alla lettura di tutte le righe presenti nel file dalla 2° riga in poi
void F_leggi_nodo_arco(Grafo G, FILE *fd,char *arr);                // Costruisce gli archi del grafo
void *F_analizza_dato_letto(int tipodato,char *arr,void *elem,int i,FILE *fd);   // Converte il dato letto da file per gestirlo nell'inserimento nel grafo
void *F_cerca_elem_grafo(Grafo G,void *elem,FILE *fd);                           // Ricerca un determinato nodo presente nel grafo (usato per gestire gli archi)
float F_leggi_peso(int infopeso,FILE *fd,char *arr);                    // Legge da file il peso dell'arco

#endif //INC_5_ESERCIZIO_5_GRAFI_L_PARSER_H
