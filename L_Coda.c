#include "L_Coda.h"
#include <stdio.h>
#include <stdlib.h>

/* Inserimento in coda di un nuovo elemento */
Coda F_enqueue(Coda C,void *elem)
{
    Coda nuovo_elemento=(struct struttura_elemento_coda *)malloc(sizeof(struct struttura_elemento_coda));

    /* Inserimento del nuovo elemento in coda */
    if(nuovo_elemento!=NULL)
    {
        nuovo_elemento->elemPtr=elem;
        nuovo_elemento->nextPtr=NULL;

        if(C==NULL) C=nuovo_elemento;
        else
        {
            Coda Tmp=C;
            while(Tmp->nextPtr!=NULL)
                Tmp=Tmp->nextPtr;
            Tmp->nextPtr=nuovo_elemento;
        }
    }else
        puts("\nErrore allocazione elemento coda!\n");

    return C;
}

/* Rimozione dell'elemento in in testa alla coda */
Coda F_dequeue(Coda C)
{
    Coda Tmp=NULL;

    if(C!=NULL)
    {
        Tmp=C->nextPtr;
        free(C);
        C=Tmp;
    }
    return C;
}

/* Preleva nodo dalla testa */
void *F_top_coda(Coda C)
{
    if(C!=NULL)
        return(C->elemPtr);
    else
        return NULL;
}
