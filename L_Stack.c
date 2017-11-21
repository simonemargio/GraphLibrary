//
// Created by ikaros on 02/10/2017.
//

#include "L_Stack.h"
#include "stdio.h"
#include "stdlib.h"

/* Inserimento di un valore in cima */
Stack F_push(Stack P,void *T)
{
    Stack nuovo_elemento=malloc(sizeof(struct struttura_elemento_pila));

    if(nuovo_elemento!=NULL)
    {
        nuovo_elemento->elemPtr=T;
        nuovo_elemento->nextPtr=P;
        P=nuovo_elemento;
    }
    else
    {
        puts("\nErrore allocazione elemento pila!\n");
    }
    return P;
}

/* Rimuovi nodo dalla cima */
Stack F_pop(Stack P)
{
    Stack Tmp=NULL;

    if(P!=NULL)
    {
        Tmp=P->nextPtr;
        free(P);
        P=Tmp;
    }
    return P;
}

/* Preleva nodo dalla cima */
void *F_top(Stack P)
{
    if(P!=NULL)
        return(P->elemPtr);
    else
        return NULL;
}

