//
// Created by ikaros on 02/10/2017.
//

#ifndef INC_1_L_STACK_H
#define INC_1_L_STACK_H

/* Struttura di un elemento dello stack */
struct struttura_elemento_pila
{
    void *elemPtr;
    struct struttura_elemento_pila *nextPtr;
};

/* Creazione di alias per semplificarne l'uso */
typedef struct struttura_elemento_pila *Stack;

Stack F_push(Stack P,void  *T); // Inserimento di un valore in cima allo stack
Stack F_pop(Stack P);           // Rimuovi nodo dalla cima
void *F_top(Stack P);          // Preleva nodo dalla cima



#endif //INC_1_L_STACK_H
