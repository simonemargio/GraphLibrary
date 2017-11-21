//
// Created by ikaros on 02/11/2017.
//

#ifndef INC_1_L_CODA_H
#define INC_1_L_CODA_H

struct struttura_elemento_coda
{
    void *elemPtr;
    struct struttura_elemento_coda *nextPtr;
};

typedef struct struttura_elemento_coda *Coda;

Coda F_enqueue(Coda C,void *elem);
Coda F_dequeue(Coda C);
void *F_top_coda(Coda C);


#endif //INC_1_L_CODA_H
