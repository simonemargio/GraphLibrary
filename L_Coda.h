//
// Created by ikaros on 02/11/2017.
//

#ifndef INC_1_L_CODA_H
#define INC_1_L_CODA_H

/* Struttura della coda */
struct struttura_elemento_coda
{
    void *elemPtr; // Puntatore all'elemento
    struct struttura_elemento_coda *nextPtr; // Puntatore all'elemento successivo
};

typedef struct struttura_elemento_coda *Coda;

Coda F_enqueue(Coda C,void *elem);  // Inserimento in coda di un nuovo elemento
Coda F_dequeue(Coda C);             // Rimozione dell'elemento in in testa alla coda
void *F_top_coda(Coda C);           // Preleva nodo dalla testa

#endif //INC_1_L_CODA_H
